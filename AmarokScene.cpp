/***************************************************************************
 *                                                                         *
 *   This file is part of the Coolbar project,                             *
 *       http://www.gitorious.org/qt4-gadgets/coolbar                      *
 *                                                                         *
 *   Copyright (C) 2009 by Enrico Ros <enrico.ros@gmail.com>               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "AmarokScene.h"

#include "ButtonElement.h"
#include "EqualizerElement.h"
#include "FlamesElement.h"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QPixmap>

// uncomment following to enable animations on relayouting
#define ANIMATE_LAYOUTING


#ifdef ANIMATE_LAYOUTING
#include <QPropertyAnimation>
#define ENRICO_ANIMATE_PARAM(object, propName, duration, endValue) \
    {QPropertyAnimation * ani = new QPropertyAnimation(object, propName, object); \
    ani->setEasingCurve(QEasingCurve::OutCubic); \
    ani->setDuration(duration); \
    ani->setEndValue(endValue); \
    ani->start(QPropertyAnimation::DeleteWhenStopped);}
#else
#define ENRICO_ANIMATE_PARAM(object, propName, duration, endValue) \
    object->setProperty(propName, endValue);
#endif


AmarokCoolbarScene::AmarokCoolbarScene(QObject * parent)
  : CoolbarScene(parent)
  , m_buttonMode(SplittedButtons)
{
    // create equalizer
    m_equalizer = new EqualizerElement;
    m_equalizer->setZValue(-1);
    addItem(m_equalizer);

    // create flames
    m_flames = new FlamesElement;
    m_flames->setZValue(-2);
    addItem(m_flames);

    // create buttons
    const QString buttonPixmaps[4] = {
        ":/data/button-prev-64.png",
        ":/data/button-play-64.png",
        ":/data/button-stop-64.png",
        ":/data/button-next-64.png"
    };
    for (int b = 0; b < 4; b++) {
        m_buttons[b] = new ButtonElement(QPixmap(buttonPixmaps[b]));
        m_buttons[b]->setZValue(0);
        connect(m_buttons[b], SIGNAL(clicked()), m_flames, SLOT(pulse()));
        addItem(m_buttons[b]);
    }
}

void AmarokCoolbarScene::setEqualizerVisible(bool visible)
{
    m_equalizer->setVisible(visible);
}

bool AmarokCoolbarScene::equalizerVisible() const
{
    return m_equalizer;
}

void AmarokCoolbarScene::setButtonMode(ButtonMode mode)
{
    if (m_buttonMode != mode) {
        m_buttonMode = mode;
        updateElementsLayout(sceneRect());
    }
}

AmarokCoolbarScene::ButtonMode AmarokCoolbarScene::buttonMode() const
{
    return m_buttonMode;
}

void AmarokCoolbarScene::updateElementsLayout(const QRectF & newBounds)
{
    // update base elements
    CoolbarScene::updateElementsLayout(newBounds);
    SizeMode mode = dynamicSizeMode();

    // update equalizer
    QSizeF s;
    int left, top;
    switch (mode) {
        default:
            s = QSizeF(4 * newBounds.width() / 10, newBounds.height() / 2);
            if (mode == DesktopSize) {
                left = newBounds.center().x() - s.width() / 2;
                top = newBounds.bottom() - s.height();
            } else {
                left = newBounds.width() - (s.width() + 10);
                top = newBounds.center().y() - s.height() / 3;
            }
            ENRICO_ANIMATE_PARAM(m_equalizer, "size", 500, s);
            ENRICO_ANIMATE_PARAM(m_equalizer, "pos", 300, QPointF(left, top));
            ENRICO_ANIMATE_PARAM(m_equalizer, "colorness", 2000, 0.0);
            break;
        case IDeviceSize:
            ENRICO_ANIMATE_PARAM(m_equalizer, "size", 500, newBounds.size());
            ENRICO_ANIMATE_PARAM(m_equalizer, "pos", 300, QPointF(0, 0));
            ENRICO_ANIMATE_PARAM(m_equalizer, "colorness", 2000, 1.0);
            break;
    }

    // update buttons
    switch (mode) {
        case DesktopSize:
            switch (m_buttonMode) {
                case SplittedButtons:
                    top = newBounds.center().y() - 64/2;
                    left = 10;
                    ENRICO_ANIMATE_PARAM(m_buttons[0], "pos", 300, QPointF(left, top));
                    left += 64 + 4;
                    ENRICO_ANIMATE_PARAM(m_buttons[2], "pos", 300, QPointF(left, top));
                    left = newBounds.right() - (64 + 4 + 64 + 10);
                    ENRICO_ANIMATE_PARAM(m_buttons[1], "pos", 300, QPointF(left, top));
                    left += 64 + 4;
                    ENRICO_ANIMATE_PARAM(m_buttons[3], "pos", 300, QPointF(left, top));
                    break;

                case VerticalStack:
                    top = 0;
                    left = newBounds.center().x() - 2 * (64 + 4);
                    for (int b = 0; b < 4; b++) {
                        ENRICO_ANIMATE_PARAM(m_buttons[b], "pos", 300, QPointF(left, top));
                        left += 64 + 4;
                    }
                    break;
            }
            for (int b = 0; b < 4; b++)
                ENRICO_ANIMATE_PARAM(m_buttons[b], "size", 500, QSizeF(64, 64));
            break;

        default:
            left = newBounds.center().x() - 2 * (32 + 4);
            if (mode == NetbookSize)
                left = 10;
            top = newBounds.center().y() - 32 / 2;
            for (int b = 0; b < 4; b++) {
                ENRICO_ANIMATE_PARAM(m_buttons[b], "size", 500, QSizeF(32, 32));
                ENRICO_ANIMATE_PARAM(m_buttons[b], "pos", 300, QPointF(left, top));
                left += 32 + 4;
            }
            break;
    }

    // update flames
    s = QSizeF(newBounds.width() / 2, 2 * newBounds.height() / 3);
    if (mode == DesktopSize)
        top = newBounds.height() - 2 * s.height() / 3;
    else
        top = (newBounds.height() - s.height()) / 2;
    m_flames->setVisible(mode != IDeviceSize);
    ENRICO_ANIMATE_PARAM(m_flames, "size", 500, s);
    ENRICO_ANIMATE_PARAM(m_flames, "pos", 300, QPointF(0, top));
}
