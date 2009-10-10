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

#include "CoolbarTheme.h"

CoolbarTheme::CoolbarTheme()
{
    // nothing to do here...
    // HACK
    loadFromDir(QDir());
}

CoolbarTheme::~CoolbarTheme()
{
    // nothing to do here...
}

void CoolbarTheme::loadFromDir(const QDir & themeDir)
{
    pixPlay = QPixmap(":/data/button-play-64.png");
    pixPause = QPixmap(":/data/button-pause-64.png");
    pixStop = QPixmap(":/data/button-stop-64.png");
    pixPrev = QPixmap(":/data/button-prev-64.png");
    pixNext = QPixmap(":/data/button-next-64.png");
}
