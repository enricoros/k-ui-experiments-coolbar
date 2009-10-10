/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2009-2009 by Enrico Ros <enrico.ros@gmail.com>        *
 *   Started on 10 Oct 2009 by root.
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "CoolbarThemeV1.h"
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>

CoolbarThemeV1::CoolbarThemeV1(const QDir & themeDir)
{
    /*pixPlay = QPixmap(":/data/button-play-64.png");
    pixPause = QPixmap(":/data/button-pause-64.png");
    pixStop = QPixmap(":/data/button-stop-64.png");
    pixPrev = QPixmap(":/data/button-prev-64.png");
    pixNext = QPixmap(":/data/button-next-64.png");*/
}

static QString themeName(const QDir & themeDir)
{
    // open the theme
    QFile file(themeDir.filePath("theme.xml"));
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("themeName: can't open theme in dir '%s'", qPrintable(themeDir.path()));
        return QString();
    }

    // parse xml
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qWarning("themeName: error in XML of '%s'", qPrintable(file.fileName()));
        return QString();
    }

    // parse <theme><name>$NAME</name>...
    return doc.firstChildElement("theme").firstChildElement("name").text();
}

QList<ThemeDescription> CoolbarThemeV1::scanForThemes(const QString & baseDir)
{
    QList<ThemeDescription> themeDirs;
    QDirIterator it(baseDir, QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString dir = it.next();
        QFileInfo info(dir + QDir::separator() + "theme.xml");
        if (info.exists()) {
            ThemeDescription d;
            d.themeDir = QDir(dir);
            d.name = themeName(d.themeDir);
            themeDirs.append(d);
        }
    }
    return themeDirs;
}

QPixmap CoolbarThemeV1::elementPixmap(const QString & epId)
{
    if (!m_elementPixmaps.contains(epId)) {
        qWarning("CoolbarThemeV1::elementPixmap: element '%s' not found", qPrintable(epId));
        return QPixmap();
    }
    return m_elementPixmaps[epId];
}

