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

#ifndef __ivDLayouter_h__
#define __ivDLayouter_h__

#include "AmarokScene.h"

class ivDLayouter : public Layouter
{
    public:
        // ::Layouter
        void event(QEvent::Type, void * item, const AmarokScene &, CoolbarScene::SizeMode);
        inline QString layoutName() const { return "4D"; }
        void layout(const AmarokScene &, CoolbarScene::SizeMode);
    private:
        void sceneHovered(bool hovered, const AmarokScene &scene, CoolbarScene::SizeMode mode);
        void sliderHovered(bool hovered, const AmarokScene &scene, CoolbarScene::SizeMode mode);
};

#endif
