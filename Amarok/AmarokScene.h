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

#ifndef __AmarokCoolbarScene_h__
#define __AmarokCoolbarScene_h__

#include "Coolbar/CoolbarScene.h"
class ButtonElement;
class BarAnalyzerElement;
class FlameElement;

/// Amarok Specific Methods
class AmarokScene : public CoolbarScene
{
    Q_OBJECT
    public:
        AmarokScene(QObject * parent = 0);

        void setAnalyzerVisible(bool visible);
        bool analyzerVisible() const;

    protected:
        // ::CoolbarScene
        void updateElementsLayout(const QRectF & newBounds);

    private:
        ButtonElement * m_buttons[4];
        BarAnalyzerElement * m_barAnalyzer;
        FlameElement * m_flame;
};

#endif
