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

#include "EqualizerElement.h"

#include <QDebug>
#include <QPainter>
#include <QTimer>

#define FAKE_SIZE 20

EqualizerElement::EqualizerElement(QGraphicsItem * parent)
  : QGraphicsWidget(parent)
  , m_colorness(0.0)
{
    // update periodically
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotGenFakeValues()));
    timer->start(40);
    slotGenFakeValues();
}

qreal EqualizerElement::colorness() const
{
    return m_colorness;
}

void EqualizerElement::setColorness(qreal value)
{
    if (value != m_colorness) {
        m_colorness = value;
        update();
    }
}

void EqualizerElement::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    // compute constraints
    QSizeF size = this->size();
    if (m_fakeData.isEmpty() || !size.isValid())
        return;
    qreal width = size.width();
    qreal height = size.height();
    int bars = m_fakeData.size();
    qreal barWidth = width / (qreal)bars;

    QLinearGradient lg(0, 0, 0, height);
    QColor col = QColor::fromHsvF(m_colorness, m_colorness, 1.0);
    col.setAlpha(255); lg.setColorAt(0.0, col);
    col.setAlpha(200); lg.setColorAt(0.4, col);
    col.setAlpha(20);  lg.setColorAt(1.0, col);

    // draw bars
    for (int i = 0; i < bars; i++) {
        qreal left = width * (qreal)i / (qreal)bars;
        qreal barHeight = m_fakeData[i] * height;
        painter->fillRect(QRectF(left, height - barHeight, barWidth, barHeight), lg);
    }
}

void EqualizerElement::slotGenFakeValues()
{
    if (m_fakeData.size() != FAKE_SIZE)
        m_fakeData.resize(FAKE_SIZE);
    for (int i = 0; i < FAKE_SIZE; i++) {
        qreal newTarget = (((qreal)(qrand() % 1000) / 990.0) + ((qreal)(qrand() % 1000) / 990.0)) / 2.0;
        m_fakeData[i] += (newTarget - m_fakeData[i]) * 0.2;
        m_fakeData[i] *= (qreal)(FAKE_SIZE - i) / (qreal)(FAKE_SIZE);
    }
    update();
}
