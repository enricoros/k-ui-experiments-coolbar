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

#ifndef __EqualizerElement_h__
#define __EqualizerElement_h__

#include <QGraphicsWidget>
#include <QVector>

class EqualizerElement : public QGraphicsWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal colorness READ colorness WRITE setColorness)
    public:
        EqualizerElement(QGraphicsItem * parent = 0);

        // properties
        qreal colorness() const;
        void setColorness(qreal);

        // ::QGraphicsItem
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    private Q_SLOTS:
        void slotGenFakeValues();

    private:
        QVector<qreal> m_fakeData;
        QVector<qreal> m_fakeTargets;
        qreal m_colorness;
};

#endif
