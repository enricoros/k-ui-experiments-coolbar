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

#include "FlamesElement.h"
#include "Coolbar/CoolbarAnimation.h"
#include <QPainter>
#include <QSvgRenderer>


FlamesElement::FlamesElement(QGraphicsItem * parent)
  : QGraphicsWidget(parent)
  , m_renderer(new QSvgRenderer)
  , m_value(0.0)
{
    m_renderer->load(QString(":/data/flames.svg"));
}

void FlamesElement::pulse()
{
    Coolbar::animateObjectProperty(this, "value", 300, 0.0, 1.0);
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
