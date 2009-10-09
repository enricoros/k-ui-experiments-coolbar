/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2009-2009 by Enrico Ros <enrico.ros@gmail.com>        *
 *   Started on 9 Oct 2009 by root.
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "AmarokCoolarScene.h"

#include "EqualizerElement.h"

#include <QDebug>
#include <QGraphicsEllipseItem>

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

AmarokCoolarScene::AmarokCoolarScene(QObject * parent)
  : CoolarScene(parent)
  , m_equalizer(0)
{
    // create equalizer
    m_equalizer = new EqualizerElement;
    addItem(m_equalizer);
}

void AmarokCoolarScene::setEqualizerVisible(bool visible)
{
    m_equalizer->setVisible(visible);
}

bool AmarokCoolarScene::equalizerVisible() const
{
    return m_equalizer;
}

void AmarokCoolarScene::updateElementsLayout(const QRectF & newBounds)
{
    // update base elements
    CoolarScene::updateElementsLayout(newBounds);
    SizeMode mode = dynamicSizeMode();

    // update equalizer
    switch (mode) {
        default:
            ENRICO_ANIMATE_PARAM(m_equalizer, "size", 500, QSizeF(newBounds.width() / 4, newBounds.height() / 2));
            ENRICO_ANIMATE_PARAM(m_equalizer, "pos", 300, QPointF(newBounds.center() - m_equalizer->rect().center()));
            break;
        case IDeviceSize:
            ENRICO_ANIMATE_PARAM(m_equalizer, "size", 500, newBounds.size());
            ENRICO_ANIMATE_PARAM(m_equalizer, "pos", 300, QPointF(0, 0));
            break;
    }
}
