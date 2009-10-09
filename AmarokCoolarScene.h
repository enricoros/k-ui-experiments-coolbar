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

#ifndef __AmarokCoolarScene_h__
#define __AmarokCoolarScene_h__

#include "CoolarScene.h"
class EqualizerElement;
class ButtonElement;

/// Amarok Specific Methods
class AmarokCoolarScene : public CoolarScene
{
    Q_OBJECT
    public:
        AmarokCoolarScene(QObject * parent = 0);

        void setEqualizerVisible(bool visible);
        bool equalizerVisible() const;

        enum ButtonMode { SplittedButtons = 0, VerticalStack = 1 };
        void setButtonMode(ButtonMode mode);
        ButtonMode buttonMode() const;

    protected:
        // ::CoolarScene
        void updateElementsLayout(const QRectF & newBounds);

    private:
        EqualizerElement * m_equalizer;
        ButtonElement * m_buttons[4];
        ButtonMode m_buttonMode;
};

#endif
