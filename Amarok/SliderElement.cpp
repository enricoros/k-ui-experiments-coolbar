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

#include "SliderElement.h"

#include "Coolbar/CoolbarAnimation.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPainter>

SliderElement::SliderElement(CoolbarScene * scene, QGraphicsItem * parent)
  : CoolbarElement(scene, parent)
  , m_value(0.35)
{
}

qreal SliderElement::value() const
{
    return m_value;
}

void SliderElement::setValue(qreal value)
{
    if (value != m_value && value >= 0.0 && value <= 1.0) {
        m_value = value;
        update();
    }
}

void SliderElement::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
        setValue(event->pos().x()/rect().width());
}

void SliderElement::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        Coolbar::animateObjectProperty(this, "value", 150, event->pos().x()/rect().width());
}

void SliderElement::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    // compute constraints
    QSizeF size = this->size();
    if (!size.isValid())
        return;

    QRectF r = rect();
    qreal rnd = r.height()/4.0;

    QColor textColor(255,255,255,196);
    painter->setPen(textColor);
    painter->drawRoundedRect(r, rnd, rnd);

    textColor.setAlpha(2*textColor.alpha()/3);
    painter->setPen(Qt::NoPen);
    painter->setBrush(textColor);
    
    r.adjust(3, 3, -3, -3);
    QRectF sr = r;
    
    rnd = r.height()/4.0;
    sr.setRight(r.width()*m_value);
    painter->drawRoundedRect(sr, rnd, rnd);

    textColor.setAlpha(0xff);
    painter->setBrush(textColor);
    sr.setLeft(sr.right()-sr.height()*1.618);
    sr.moveLeft(sr.left() + sr.width()/2.0);
    if (sr.left() < r.left())
        sr.moveLeft(r.left());
    if (sr.right() > r.right())
        sr.moveRight(r.right());
    painter->drawRoundedRect(sr, rnd, rnd);
}
