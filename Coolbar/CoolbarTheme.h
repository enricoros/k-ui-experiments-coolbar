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
#include <QPixmap>

// SUBJECT TO BIG CHANGES
// SUBJECT TO BIG CHANGES
// SUBJECT TO BIG CHANGES

class CoolbarTheme
{
    public:
        CoolbarTheme();
        virtual ~CoolbarTheme();

        void loadFromDir(const QDir & themeDir);
        //void loadFromXml(const QString & themeFileName);
        //void loadFromData(const QByteArray & themeData);

        //virtual QPixmap elementPixmap(const QString & epId) = 0;

        // ### TEMP : public pixmaps
        QPixmap pixPlay, pixPause, pixStop, pixNext, pixPrev;

    //private:
};

#endif
