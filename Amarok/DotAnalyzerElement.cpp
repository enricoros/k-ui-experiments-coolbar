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

#include "DotAnalyzerElement.h"

#include <QDebug>
#include <QPainter>
#include <QTimer>

DotAnalyzerElement::DotAnalyzerElement(CoolbarScene * scene, QGraphicsItem * parent)
  : VisualizationElement(scene, parent)
  , m_colorness(0.0)
{
}

qreal DotAnalyzerElement::colorness() const
{
    return m_colorness;
}

void DotAnalyzerElement::setColorness(qreal value)
{
    if (value != m_colorness) {
        m_colorness = value;
        update();
    }
}

void DotAnalyzerElement::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    // compute constraints
    QSizeF size = this->size();
    if (m_data.isEmpty() || !size.isValid())
        return;
    int bars = ((m_data.size() / 2) & 0xFE) + 1;
    int halfBars = bars / 2;
    qreal width = size.width();
    qreal barWidth = width / (qreal)bars;
    qreal barHeight = size.height();

    QColor col = QColor::fromHsvF(m_colorness, 1.0 - ((1.0 - m_colorness) * (1.0 - m_colorness)), 1.0);

    // draw bars
    for (int i = 0; i < bars; i++) {
        qreal alpha = 0.85*m_data[i <= halfBars ? halfBars - i : i - halfBars];
        qreal left = width * (qreal)i / (qreal)bars;
        qreal cx = left + barWidth / 2;
        qreal cy = 0.9*barHeight;
        qreal w = 1.4 * alpha * barWidth;
        qreal h = 0.6 * alpha * barHeight;
        col.setAlphaF(qBound(0.0, 2 * alpha, 1.0));
#if 0
        painter->fillRect(QRectF(cx - w/2, cy - h/2, w, h), col);
#else
        painter->setPen(Qt::NoPen);
        painter->setBrush(col);
        painter->drawRoundedRect(QRectF(cx - w/2, cy - h/2, w, h), 6, 6, Qt::AbsoluteSize);
#endif
    }
}
