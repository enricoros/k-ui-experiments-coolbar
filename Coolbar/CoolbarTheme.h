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

#ifndef __CoolbarTheme_h__
#define __CoolbarTheme_h__

#include <QDir>
#include <QPalette>
#include <QPixmap>
#include <QString>

class CoolbarTheme
{
    public:
        struct Description {
            QString name;
            QDir themeDir;
            int provider;
        };

        virtual QString themeName() const = 0;
        virtual QPixmap elementPixmap(const QString & epId) const = 0;
        virtual QPalette palette() const = 0;
        virtual QBrush brush(QPalette::ColorRole) const = 0;
};

#endif
