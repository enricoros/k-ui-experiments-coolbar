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

#include "FlameElement.h"
#include "Coolbar/CoolbarAnimation.h"
#include "Coolbar/CoolbarTheme.h"
#include <QPainter>
#include <QSvgRenderer>


FlameElement::FlameElement(CoolbarScene * scene, QGraphicsItem * parent)
  : CoolbarElement(scene, parent)
  , m_renderer(0)
  , m_value(0.0)
{
    // customize item
    setZValue(-2);
}

FlameElement::~FlameElement()
{
    delete m_renderer;
}

void FlameElement::pulse()
{
    Coolbar::animateObjectProperty(this, "pulseValue", 300, 0.0, 1.0);
}

void FlameElement::themeChanged()
{
    if (CoolbarTheme * t = theme()) {
        QString flameFile = t->elementFile("flameFile");
        delete m_renderer;
        m_renderer = 0;
        if (!flameFile.isEmpty()) {
            m_renderer = new QSvgRenderer(flameFile);
            if (!m_renderer->isValid()) {
                qWarning("FlameElement::themeChanged: broken Flame file in this Theme");
                delete m_renderer;
                m_renderer = 0;
            }
        } else
            qWarning("FlameElement::themeChanged: no Flame file in this Theme");
    }
}

void FlameElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!m_renderer || m_value <= 0.0)
        return;
    if (m_value < 1.0)
        painter->setOpacity(m_value);
    m_renderer->render(painter, rect());
}

qreal FlameElement::pulseValue() const
{
    return m_value;
}

void FlameElement::setPulseValue(qreal value)
{
    if (value != m_value) {
        m_value = value;
        update();
    }
}
