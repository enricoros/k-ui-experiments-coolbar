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

#ifndef __FlameElement_h__
#define __FlameElement_h__

#include "Coolbar/CoolbarElement.h"
#include <QPixmap>
class QSvgRenderer;

class FlameElement : public CoolbarElement
{
    Q_OBJECT
    Q_PROPERTY(qreal pulseValue READ pulseValue WRITE setPulseValue)
    public:
        FlameElement(CoolbarScene *, QGraphicsItem * parent = 0);
        ~FlameElement();

    public Q_SLOTS:
        void pulse();

    protected:
        // ::CoolbarElement
        void themeChanged();

        // ::QGraphicsItem
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    private:
        qreal pulseValue() const;
        void setPulseValue(qreal);
        QSvgRenderer * m_renderer;
        qreal m_value;
};

#endif
