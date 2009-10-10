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

class CoolbarThemeV1 : public CoolbarTheme
{
    public:
        enum { ProviderCode = 0x001 };
        CoolbarThemeV1(const QDir & themeDir);

        // ::CoolbarTheme
        QString themeName() const;
        QPixmap elementPixmap(const QString &) const;
        QPalette palette() const;
        QBrush brush(QPalette::ColorRole) const;

        static QList<CoolbarTheme::Description> scanForV1Themes(const QString & baseDir);

    private:
        bool loadThemeFromDir(const QDir & themeDir);
        QString m_name;
        QMap<QString, QPixmap> m_elementPixmaps;
        QPalette m_palette;
};

#endif
