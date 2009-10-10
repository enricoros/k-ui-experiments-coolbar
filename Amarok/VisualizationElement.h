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

#ifndef __VisualizationElement_h__
#define __VisualizationElement_h__

#include "Coolbar/CoolbarElement.h"

class VisualizationElement : public CoolbarElement
{
    Q_OBJECT
    public:
        VisualizationElement(CoolbarScene *, QGraphicsItem * parent = 0);

        // temporary API
        typedef QVector<qreal> Data;
        void setData(const Data &);
        Data data() const;

    protected:
        Data m_data;

    private Q_SLOTS:
        void slotGenFakeValues();
};

#endif
