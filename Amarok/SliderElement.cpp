/***************************************************************************
 *                                                                         *
 *   This file is part of the Coolbar project,                             *
 *       http://www.gitorious.org/qt4-gadgets/coolbar                      *
 *                                                                         *
 *   Copyright (C) 2009 by Thomas Luebking <thomas.luebking@web.de>        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "SliderElement.h"

#include "Coolbar/CoolbarAnimation.h"
#include "Coolbar/CoolbarScene.h"
#include <QPropertyAnimation>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPainter>

SliderElement::SliderElement(CoolbarScene * scene, QGraphicsItem * parent)
  : CoolbarElement(scene, parent)
  , m_value(0.0)
{
    connect (&m_hoverPropagationDelay, SIGNAL(timeout()), this, SLOT(delayedHoverPropagation()));
}

qreal SliderElement::value() const
{
    return m_value;
}

void SliderElement::setValue(qreal value)
{
    if (value != m_value && value >= 0.0 && value <= 1.0) {
        m_value = value;
        emit valueChanged(value);
        update();
    }
}

void SliderElement::delayedHoverPropagation()
{
    m_hoverPropagationDelay.stop();
    scene()->propagateEvent(this, isHovered() ? QEvent::Enter : QEvent::Leave);
}

void SliderElement::hoverEnterEvent(QGraphicsSceneHoverEvent *ev)
{
    CoolbarElement::hoverEnterEvent(ev);
    m_hoverPropagationDelay.start(200);
}

void SliderElement::hoverLeaveEvent(QGraphicsSceneHoverEvent *ev)
{
    CoolbarElement::hoverLeaveEvent(ev);
    m_hoverPropagationDelay.start(200);
}

void SliderElement::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (event->pos().x() < rect().left() || event->pos().x() > rect().right())
            return; // don't slide out
        qreal value = event->pos().x()/rect().width();
        setValue(value);
        if (value != event->lastPos().x()/rect().width())
            emit dragged(value);
    }
}

void SliderElement::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
//         emit valueChanged(qMin(qMax(.0, event->pos().x()), rect().width()) / rect().width());
        QPropertyAnimation *ani = animate("value", 250, event->pos().x()/rect().width());
        connect (this, SIGNAL(dragged(qreal)), ani, SLOT(stop()));
        // emit dragged signal constrained to slider length
        scene()->propagateEvent(this, QEvent::MouseButtonPress);
    }
}

void SliderElement::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        scene()->propagateEvent(this, QEvent::MouseButtonRelease);
}

void SliderElement::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    // compute constraints
    QSizeF size = this->size();
    if (!size.isValid())
        return;

    QRectF r = rect();
    qreal rnd = r.height()/4.0;

    QColor textColor(255,255,255,128);
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

void SliderElement::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    const qreal delta = event->delta() < 0 ? 0.05 : - 0.05;
    animate("value", 150, qMin(qMax(0.0, m_value + delta), 1.0));
}

