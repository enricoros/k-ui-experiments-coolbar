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

#ifndef __ButtonElement_h__
#define __ButtonElement_h__

#include <QGraphicsWidget>
#include <QPixmap>

class ButtonElement : public QGraphicsWidget
{
    Q_OBJECT
    public:
        ButtonElement(const QPixmap & hiqPixmap, QGraphicsItem * parent = 0);

        // ::QGraphicsItem
        void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
        void mousePressEvent(QGraphicsSceneMouseEvent * event);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    Q_SIGNALS:
        void clicked();

    private:
        QPixmap m_pixmap;
        bool m_hovered;
};

#endif
