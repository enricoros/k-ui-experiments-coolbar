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

#include "CoolbarThemeV1.h"
#include <QApplication>
#include <QBrush>
#include <QDir>
#include <QDirIterator>
#include <QDomDocument>
#include <QDomElement>
#include <QFileInfo>
#include <QFile>
#include <QLinearGradient>
#include <QPalette>

CoolbarThemeV1::CoolbarThemeV1(const QDir & themeDir)
{
    loadThemeFromDir(themeDir);
}

QString CoolbarThemeV1::themeName() const
{
    return m_name;
}

QString CoolbarThemeV1::elementFile(const QString & efId) const
{
    if (!m_elementFiles.contains(efId)) {
        qWarning("CoolbarThemeV1::elementFile: element '%s' not found", qPrintable(efId));
        return QString();
    }
    return m_elementFiles[efId];
}

QPixmap CoolbarThemeV1::elementPixmap(const QString & epId) const
{
    if (!m_elementPixmaps.contains(epId)) {
        qWarning("CoolbarThemeV1::elementPixmap: element '%s' not found", qPrintable(epId));
        return QPixmap();
    }
    return m_elementPixmaps[epId];
}

QPalette CoolbarThemeV1::palette() const
{
    return m_palette;
}

QBrush CoolbarThemeV1::brush(QPalette::ColorRole cr) const
{
    return m_palette.brush(cr);
}


static QString readXmlName(const QDir & themeDir)
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

QList<CoolbarTheme::Description> CoolbarThemeV1::scanForV1Themes(const QString & baseDir)
{
    QList<CoolbarTheme::Description> themeDirs;
    QDirIterator it(baseDir, QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QDir dir(it.next());
        QFileInfo info(dir.filePath("theme.xml"));
        if (info.exists()) {
            CoolbarTheme::Description d;
            d.name = readXmlName(dir);
            d.themeDir = dir;
            d.provider = ProviderCode;
            themeDirs.append(d);
        }
    }
    return themeDirs;
}

#include <QDebug>
static QBrush readBrush(const QDomElement & brushElement)
{
    // if it's a gradient
    if (brushElement.tagName() == "gradient") {
        QLinearGradient lg;
        QStringList from = brushElement.attribute("from").split(",", QString::SkipEmptyParts);
        QStringList to = brushElement.attribute("to").split(",", QString::SkipEmptyParts);
        if (from.size() == 2 && to.size() == 2) {
            lg.setCoordinateMode(QLinearGradient::StretchToDeviceMode);
            lg.setStart(from[0].toDouble(), from[1].toDouble());
            lg.setFinalStop(to[0].toDouble(), to[1].toDouble());
        } else {
            qWarning("readBrush: invalid from/to specification for brush");
            return QBrush();
        }
        for(QDomElement eColor = brushElement.firstChildElement(); !eColor.isNull(); eColor = eColor.nextSiblingElement()) {
            QString colorString = eColor.text().trimmed();
            qreal at = eColor.attribute("at").toDouble();
            lg.setColorAt(at, QColor(colorString));
        }
        return lg;
    }
    // if it's a color
    else if (brushElement.tagName() == "color") {
        QColor color(brushElement.text().trimmed());
        return color;
    }

    // unknown element
    qWarning("readBrush: invalid brush name '%s'", qPrintable(brushElement.tagName()));
    return QBrush();
}

bool CoolbarThemeV1::loadThemeFromDir(const QDir & themeDir)
{
    // open the theme
    QFile file(themeDir.filePath("theme.xml"));
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("CoolbarThemeV1::loadThemeFromDir: can't open theme in dir '%s'", qPrintable(themeDir.path()));
        return false;
    }

    // parse xml
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qWarning("CoolbarThemeV1::loadThemeFromDir: error in XML of '%s'", qPrintable(file.fileName()));
        return false;
    }

    // read name
    QDomElement rootElement = doc.firstChildElement("theme");
    m_name = rootElement.firstChildElement("name").text();

    // read all files
    m_elementFiles.clear();
    for (QDomElement eElement = rootElement.firstChildElement("resource"); !eElement.isNull(); eElement = eElement.nextSiblingElement("resource")) {
        QString name = eElement.attribute("name");
        QString fileName = eElement.attribute("file");
        m_elementFiles[name] = themeDir.filePath(fileName);
    }

    // read all pixmaps
    m_elementPixmaps.clear();
    for (QDomElement eElement = rootElement.firstChildElement("element"); !eElement.isNull(); eElement = eElement.nextSiblingElement("element")) {
        QString name = eElement.attribute("name");
        QString pixmapName = eElement.attribute("pixmap");
        QPixmap pixmap(themeDir.filePath(pixmapName));
        if (pixmap.isNull())
            qWarning("CoolbarThemeV1::loadThemeFromDir: error loading pixmap '%s'", qPrintable(themeDir.filePath(pixmapName)));
        else
            m_elementPixmaps[name] = pixmap;
    }

    // read palette
    m_palette = QApplication::palette();
    QDomElement ePal = rootElement.firstChildElement("palette");
    for (QDomElement roleElement = ePal.firstChildElement(); !roleElement.isNull(); roleElement = roleElement.nextSiblingElement()) {
        QString roleName = roleElement.tagName();
        if (roleName == "background-brush")
            m_palette.setBrush(QPalette::Window, readBrush(roleElement.firstChildElement()));
        else
            qWarning("CoolbarThemeV1::loadThemeFromDir: unknown palette element '%s'", qPrintable(roleName));
    }

    // cool
    return true;
}
