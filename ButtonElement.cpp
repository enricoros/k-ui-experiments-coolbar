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

#include "ButtonElement.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>

ButtonElement::ButtonElement(const QPixmap & hiqPixmap, QGraphicsItem * parent)
  : QGraphicsWidget(parent)
  , m_pixmap(hiqPixmap)
  , m_hovered(false)
{
    setAcceptHoverEvents(true);
    resize(hiqPixmap.size());
}

void ButtonElement::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    m_hovered = true;
    update();
}

void ButtonElement::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    m_hovered = false;
    update();
}

void ButtonElement::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();
}

void ButtonElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setOpacity(m_hovered ? 1.0 : 0.4);
    painter->drawPixmap(rect().toAlignedRect(), m_pixmap);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
}
