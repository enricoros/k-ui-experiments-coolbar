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

#ifndef __CoolbarThemeV1_h__
#define __CoolbarThemeV1_h__

#include "CoolbarTheme.h"
#include <QDir>
#include <QMap>
#include <QPixmap>

struct ThemeDescription {
    QString name;
    QDir themeDir;
};

class CoolbarThemeV1 : public CoolbarTheme
{
    public:
        static QList<ThemeDescription> scanForThemes(const QString & baseDir);

        CoolbarThemeV1(const QDir & themeDir);

        // ::CoolbarTheme
        QPixmap elementPixmap(const QString & epId);

    private:
        QMap<QString, QPixmap> m_elementPixmaps;
};

#endif
