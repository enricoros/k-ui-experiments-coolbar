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

#include "VisualizationElement.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QTimer>

#define FAKE_SIZE 20

VisualizationElement::VisualizationElement(CoolbarScene * scene, QGraphicsItem * parent)
  : CoolbarElement(scene, parent)
{
    // customize item
    setZValue(-1);

    // generate fake values periodically
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotGenFakeValues()));
    timer->start(40);
    slotGenFakeValues();
}

void VisualizationElement::setData(const Data & data)
{
    m_data = data;
    update();
}

VisualizationElement::Data VisualizationElement::data() const
{
    return m_data;
}

void VisualizationElement::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();
}

void VisualizationElement::slotGenFakeValues()
{
    if (m_data.size() != FAKE_SIZE)
        m_data.resize(FAKE_SIZE);
    for (int i = 0; i < FAKE_SIZE; i++) {
        qreal newTarget = (((qreal)(qrand() % 1000) / 990.0) + ((qreal)(qrand() % 1000) / 990.0)) / 2.0;
        m_data[i] += (newTarget - m_data[i]) * 0.2;
        m_data[i] *= (qreal)(FAKE_SIZE - i) / (qreal)(FAKE_SIZE);
    }
    update();
}
