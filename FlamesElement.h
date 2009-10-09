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

#ifndef __FlamesElement_h__
#define __FlamesElement_h__

#include <QGraphicsWidget>
#include <QPixmap>
class QSvgRenderer;

class FlamesElement : public QGraphicsWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal value READ value WRITE setValue)
    public:
        FlamesElement(QGraphicsItem * parent = 0);

        // ::QGraphicsItem
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    public Q_SLOTS:
        void pulse();

    private:
        qreal value() const;
        void setValue(qreal);
        QSvgRenderer * m_renderer;
        qreal m_value;
};

#endif
