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
#include "coolbar/CoolbarAnimation.h"
#include "coolbar/CoolbarTheme.h"


AmarokScene::AmarokScene(QObject * parent)
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
    m_buttons[0] = new ButtonElement(ButtonElement::PrevButton, this);
    m_buttons[1] = new ButtonElement(ButtonElement::PlayButton, this);
    connect(m_buttons[1], SIGNAL(clicked()), m_flames, SLOT(pulse()));
    m_buttons[2] = new ButtonElement(ButtonElement::StopButton, this);
    m_buttons[3] = new ButtonElement(ButtonElement::NextButton, this);
}

void AmarokScene::setEqualizerVisible(bool visible)
{
    m_equalizer->setVisible(visible);
}

bool AmarokScene::equalizerVisible() const
{
    return m_equalizer;
}

void AmarokScene::setButtonMode(ButtonMode mode)
{
    if (m_buttonMode != mode) {
        m_buttonMode = mode;
        updateElementsLayout(sceneRect());
    }
}

AmarokScene::ButtonMode AmarokScene::buttonMode() const
{
    return m_buttonMode;
}

void AmarokScene::updateElementsLayout(const QRectF & newBounds)
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
            Coolbar::animateObjectProperty(m_equalizer, "size", 500, s);
            Coolbar::animateObjectProperty(m_equalizer, "pos", 300, QPointF(left, top));
            Coolbar::animateObjectProperty(m_equalizer, "colorness", 2000, 0.0);
            break;
        case IDeviceSize:
            Coolbar::animateObjectProperty(m_equalizer, "size", 500, newBounds.size());
            Coolbar::animateObjectProperty(m_equalizer, "pos", 300, QPointF(0, 0));
            Coolbar::animateObjectProperty(m_equalizer, "colorness", 2000, 1.0);
            break;
    }

    // update buttons
    switch (mode) {
        case DesktopSize:
            switch (m_buttonMode) {
                case SplittedButtons:
                    top = newBounds.center().y() - 64/2;
                    left = 10;
                    Coolbar::animateObjectProperty(m_buttons[0], "pos", 300, QPointF(left, top));
                    left += 64 + 4;
                    Coolbar::animateObjectProperty(m_buttons[2], "pos", 300, QPointF(left, top));
                    left = newBounds.right() - (64 + 4 + 64 + 10);
                    Coolbar::animateObjectProperty(m_buttons[1], "pos", 300, QPointF(left, top));
                    left += 64 + 4;
                    Coolbar::animateObjectProperty(m_buttons[3], "pos", 300, QPointF(left, top));
                    break;

                case VerticalStack:
                    top = 0;
                    left = newBounds.center().x() - 2 * (64 + 4);
                    for (int b = 0; b < 4; b++) {
                        Coolbar::animateObjectProperty(m_buttons[b], "pos", 300, QPointF(left, top));
                        left += 64 + 4;
                    }
                    break;
            }
            for (int b = 0; b < 4; b++)
                Coolbar::animateObjectProperty(m_buttons[b], "size", 500, QSizeF(64, 64));
            break;

        default:
            left = newBounds.center().x() - 2 * (32 + 4);
            if (mode == NetbookSize)
                left = 10;
            top = newBounds.center().y() - 32 / 2;
            for (int b = 0; b < 4; b++) {
                Coolbar::animateObjectProperty(m_buttons[b], "size", 500, QSizeF(32, 32));
                Coolbar::animateObjectProperty(m_buttons[b], "pos", 300, QPointF(left, top));
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
    Coolbar::animateObjectProperty(m_flames, "size", 500, s);
    Coolbar::animateObjectProperty(m_flames, "pos", 300, QPointF(0, top));
}
