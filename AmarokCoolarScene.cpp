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

#include <QGraphicsEllipseItem>

// uncomment following to enable animations on relayouting
#define ANIMATE_LAYOUTING

#ifdef ANIMATE_LAYOUTING
#include <QPropertyAnimation>
#endif

QGraphicsItem * item;

AmarokCoolarScene::AmarokCoolarScene(QObject * parent)
  : CoolarScene(parent)
{
    item = addEllipse(-10, -10, 20, 20);
}

void AmarokCoolarScene::updateElementsLayout(const QRectF & newBounds)
{
    // update base elements
    CoolarScene::updateElementsLayout(newBounds);

    // update our elements
    item->setPos(newBounds.center());
}
