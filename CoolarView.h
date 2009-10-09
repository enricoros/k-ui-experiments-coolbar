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

#ifndef COOLAR_H
#define COOLAR_H

#include <QGraphicsView>
class CoolarScene;

class CoolarView : public QGraphicsView
{
    Q_OBJECT
    public:
        CoolarView(CoolarScene *, QWidget * parent = 0);

    protected:
        // ::QWidget
        void resizeEvent(QResizeEvent * event);
        QSize sizeHint() const;
        QSize minimumSizeHint() const;

    private:
        CoolarScene * m_coolarScene;

    private Q_SLOTS:
        void slotResizeView();
};

#endif
