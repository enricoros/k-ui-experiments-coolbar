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

#ifndef __ButtonElement_h__
#define __ButtonElement_h__

#include "coolbar/CoolbarElement.h"
#include <QPixmap>
class AmarokScene;

class ButtonElement : public CoolbarElement
{
    Q_OBJECT
    public:
        enum ButtonType {
            PlayButton,     PauseButton,    StopButton,
            NextButton,     PrevButton,     //TextButton, // ...
        };
        ButtonElement(ButtonType, AmarokScene *, QGraphicsItem * parent = 0);

    Q_SIGNALS:
        void clicked();

    protected:
        // ::CoolbarElement
        void themeChanged();

        // ::QGraphicsItem
        void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
        void mousePressEvent(QGraphicsSceneMouseEvent * event);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    private:
        ButtonType m_buttonType;
        QPixmap m_pixmap;
        bool m_hovered;
};

#endif
