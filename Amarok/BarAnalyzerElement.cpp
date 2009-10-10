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

#include "BarAnalyzerElement.h"

#include <QDebug>
#include <QPainter>
#include <QTimer>

BarAnalyzerElement::BarAnalyzerElement(CoolbarScene * scene, QGraphicsItem * parent)
  : VisualizationElement(scene, parent)
  , m_colorness(0.0)
{
}

qreal BarAnalyzerElement::colorness() const
{
    return m_colorness;
}

void BarAnalyzerElement::setColorness(qreal value)
{
    if (value != m_colorness) {
        m_colorness = value;
        update();
    }
}

void BarAnalyzerElement::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    // compute constraints
    QSizeF size = this->size();
    if (m_data.isEmpty() || !size.isValid())
        return;
    qreal width = size.width();
    qreal height = size.height();
    int bars = m_data.size();
    qreal barWidth = width / (qreal)bars;

    QLinearGradient lg(0, 0, 0, height);
    QColor col = QColor::fromHsvF(m_colorness, 1.0 - ((1.0 - m_colorness) * (1.0 - m_colorness)), 1.0);
    col.setAlpha(255); lg.setColorAt(0.0, col);
    col.setAlpha(200); lg.setColorAt(0.4, col);
    col.setAlpha(20);  lg.setColorAt(1.0, col);

    // draw bars
    for (int i = 0; i < bars; i++) {
        qreal left = width * (qreal)i / (qreal)bars;
        qreal barHeight = m_data[i] * height;
        painter->fillRect(QRectF(left, height - barHeight, barWidth, barHeight), lg);
    }
}
