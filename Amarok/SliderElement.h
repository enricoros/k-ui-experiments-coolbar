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

#ifndef __SliderElement_h__
#define __SliderElement_h__

#include "Amarok/VisualizationElement.h"

class SliderElement : public CoolbarElement
{
    Q_OBJECT
    Q_PROPERTY(qreal value READ value WRITE setValue)
    public:
        SliderElement(CoolbarScene *, QGraphicsItem * parent = 0);

        // properties
        qreal value() const;
        void setValue(qreal);

        // ::QGraphicsItem
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

        void mouseMoveEvent(QGraphicsSceneMouseEvent *);
        void mousePressEvent(QGraphicsSceneMouseEvent *);

    private:
        qreal m_value;
};

#endif
