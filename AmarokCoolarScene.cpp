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
            m_equalizer->resize(newBounds.width() / 4, newBounds.height() / 2);
            m_equalizer->setPos(newBounds.center() - m_equalizer->rect().center());
            break;
        case IDeviceSize:
            m_equalizer->resize(newBounds.size());
            m_equalizer->setPos(0, 0);
            break;
    }
}
