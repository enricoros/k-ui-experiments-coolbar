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

#ifndef __Amarok22Layouter_h__
#define __Amarok22Layouter_h__

#include "AmarokScene.h"

class Amarok22Layouter : public Layouter
{
    public:
        // ::Layouter
        QString layoutName() const { return "Amarok 2.2"; }
        void layout(const AmarokScene &, CoolbarScene::SizeMode);
};

#endif
