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

#include "AmarokCoolbar.h"
#include "Coolbar/CoolbarThemeV1.h"

AmarokCoolbar::AmarokCoolbar(const QString & baseDir)
  : m_scene(0)
  , m_view(0)
  , m_currentTheme(-1)
{
    m_scene = new AmarokScene;
    m_view = new CoolbarView(m_scene);
    m_themes = CoolbarThemeV1::scanForV1Themes(baseDir);
}

AmarokCoolbar::~AmarokCoolbar()
{
    delete m_scene;
    delete m_view;
}

AmarokScene * AmarokCoolbar::scene() const
{
    return m_scene;
}

CoolbarView * AmarokCoolbar::view() const
{
    return m_view;
}

void AmarokCoolbar::setTheme(int index)
{
    // skip bad index
    if (index < 0 || index >= m_themes.size() || index == m_currentTheme)
        return;

    // load theme
    CoolbarTheme * theme = new CoolbarThemeV1(m_themes[index].themeDir);
    m_scene->setTheme(theme);
}

QList<QString> AmarokCoolbar::themeNames() const
{
    QList<QString> names;
    foreach (const CoolbarTheme::Description & desc, m_themes)
        names.append(desc.name);
    return names;
}

void AmarokCoolbar::setLayout(int /*index*/)
{
    // not implemented
}

QList<QString> AmarokCoolbar::layoutNames() const
{
    QList<QString> names;
    // not implemented
    return names;
}
