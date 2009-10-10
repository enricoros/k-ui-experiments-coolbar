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

#ifndef __CoolbarView_h__
#define __CoolbarView_h__

#include <QGraphicsView>
class CoolbarScene;

class CoolbarView : public QGraphicsView
{
    Q_OBJECT
    public:
        CoolbarView(CoolbarScene *, QWidget * parent = 0);

    protected:
        // ::QWidget
        void resizeEvent(QResizeEvent * event);
        QSize sizeHint() const;
        QSize minimumSizeHint() const;

    private:
        CoolbarScene * m_coolbarScene;

    private Q_SLOTS:
        void slotResizeView();
};

#endif
