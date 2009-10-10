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

#include "coolbar/CoolbarScene.h"
class ButtonElement;
class EqualizerElement;
class FlamesElement;

/// Amarok Specific Methods
class AmarokCoolbarScene : public CoolbarScene
{
    Q_OBJECT
    public:
        AmarokCoolbarScene(QObject * parent = 0);

        void setEqualizerVisible(bool visible);
        bool equalizerVisible() const;

        enum ButtonMode { SplittedButtons = 0, VerticalStack = 1 };
        void setButtonMode(ButtonMode mode);
        ButtonMode buttonMode() const;

    protected:
        // ::CoolbarScene
        void updateElementsLayout(const QRectF & newBounds);

    private:
        ButtonMode m_buttonMode;
        ButtonElement * m_buttons[4];
        EqualizerElement * m_equalizer;
        FlamesElement * m_flames;
};

#endif
