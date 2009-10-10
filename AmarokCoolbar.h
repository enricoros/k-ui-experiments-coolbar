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

#ifndef __AmarokCoolbar_h__
#define __AmarokCoolbar_h__

#include <QList>
#include "Coolbar/CoolbarThemeV1.h"
#include "Coolbar/CoolbarView.h"
#include "AmarokScene.h"

// easy access to all the classes
class AmarokCoolbar
{
    public:
        AmarokCoolbar(const QString & baseDir);
        ~AmarokCoolbar();

        AmarokScene * scene() const;
        CoolbarView * view() const;

        void setTheme(int index);
        QList<QString> themeNames() const;

        void setLayout(int index);
        QList<QString> layoutNames() const;

    private:
        QList<ThemeDescription> m_themes;
        AmarokScene * m_scene;
        CoolbarView * m_view;
        int m_currentTheme;
};

#endif
