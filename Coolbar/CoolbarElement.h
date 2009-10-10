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

#ifndef __CoolbarElement_h__
#define __CoolbarElement_h__

#include <QGraphicsWidget>
class CoolbarScene;
class CoolbarTheme;

class CoolbarElement : public QGraphicsWidget
{
    Q_OBJECT
    public:
        CoolbarElement(CoolbarScene *, QGraphicsItem * parent = 0);
        virtual ~CoolbarElement();

    Q_SIGNALS:
        void clicked();

    protected:
        // ::QGraphicsWidget
        virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
        virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
        virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
        virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);

    protected Q_SLOTS:
        // can be reimplemented by subclasses
        virtual void themeChanged() {}

    protected:
        CoolbarScene * scene() const;
        CoolbarTheme * theme() const;
        inline bool isHovered() const { return m_hovered; }

    private:
        CoolbarElement();
        CoolbarScene * m_scene;
        bool m_hovered;
};

#endif
