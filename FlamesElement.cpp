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

#include "FlamesElement.h"

#include <QPainter>
#include <QSvgRenderer>
#include <QPropertyAnimation>

FlamesElement::FlamesElement(QGraphicsItem * parent)
  : QGraphicsWidget(parent)
  , m_renderer(new QSvgRenderer)
  , m_value(0.0)
{
    m_renderer->load(QString(":/data/flames.svg"));
}

void FlamesElement::pulse()
{
    QPropertyAnimation * ani = new QPropertyAnimation(this, "value", this);
    ani->setEasingCurve(QEasingCurve::OutQuad);
    ani->setDuration(300);
    ani->setStartValue(1.0);
    ani->setEndValue(0.0);
    ani->start(QPropertyAnimation::DeleteWhenStopped);
}

void FlamesElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (m_value <= 0.0)
        return;
    if (m_value < 1.0)
        painter->setOpacity(m_value);
    m_renderer->render(painter, rect());
}

qreal FlamesElement::value() const
{
    return m_value;
}

void FlamesElement::setValue(qreal value)
{
    if (value != m_value) {
        m_value = value;
        update();
    }
}
