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

#include "CoolbarScene.h"
#include "CoolbarAnimation.h"
#include "CoolbarLayouter.h"
#include "CoolbarTheme.h"
#include <QPainter>


CoolbarScene::CoolbarScene(QObject * parent)
  : QGraphicsScene(parent)
  , m_theme(0)
  , m_layouter(0)
  , m_animateResize(false)
  , m_animateLayouting(true)
  , m_dynamicSizeMode(DesktopSize)
{
    // sets the palette
    QPalette pal;
    pal.setColor(QPalette::Window, QColor(62, 62, 62));
    setPalette(pal);

    // sets initial sizes
    updateDynamicSize(-1);
}

CoolbarScene::~CoolbarScene()
{
    delete m_theme;
    delete m_layouter;
}

void CoolbarScene::setTheme(CoolbarTheme * theme)
{
    if (theme != m_theme) {
        // notify about the change
        CoolbarTheme * oldTheme = m_theme;
        m_theme = theme;
        emit themeChanged();

        // update screen
        updateElementsLayout(m_sceneRect);
        update();

        // delete old
        delete oldTheme;
    }
}

CoolbarTheme * CoolbarScene::theme() const
{
    return m_theme;
}

void CoolbarScene::setLayouter(CoolbarLayouter * layouter)
{
    if (layouter != m_layouter) {
        // notify about the change
        CoolbarLayouter * oldLayouter = m_layouter;
        m_layouter = layouter;
        emit layouterChanged();

        // update screen
        updateElementsLayout(m_sceneRect);
        update();

        // delete old
        oldLayouter->deleteLater();
    }
}

CoolbarLayouter * CoolbarScene::layouter() const
{
    return m_layouter;
}

void CoolbarScene::setResizeAnimationEnabled(bool on)
{
    if (on != m_animateResize)
        m_animateResize = on;
}

void CoolbarScene::setLayoutAnimationEnabled(bool on)
{
    if (on != m_animateLayouting)
        m_animateLayouting = on;
}

/// evaluate SizeMode change, reposition elements, change scene rect
void CoolbarScene::resize(const QSize & viewSize)
{
    // apply the new size, if changed
    if (viewSize == m_sceneSize)
        return;
    m_sceneSize = viewSize;
    m_sceneRect = QRectF(0, 0, m_sceneSize.width(), m_sceneSize.height());
    setSceneRect(m_sceneRect);

    // check if the SizeMode needs to be updated
    if (updateDynamicSize(viewSize.width()))
        return;

    // udate the position of the elements
    updateElementsLayout(m_sceneRect);
}

/// Query
CoolbarScene::SizeMode CoolbarScene::dynamicSizeMode() const
{
    return m_dynamicSizeMode;
}

QSize CoolbarScene::dynamicSizeHint() const
{
    return m_dynamicSizeHint;
}

/// Drawing
QColor CoolbarScene::paletteColor(QPalette::ColorRole role, int lightAdj)
{
    QColor col = palette().color(role);
    if (!lightAdj)
        return col;
    return lightAdj > 0 ? col.lighter(100 + lightAdj) : col.darker(100 - lightAdj);
}

void CoolbarScene::drawBackground(QPainter * painter, const QRectF & rect)
{
    // setup gradient
    QLinearGradient lg(0, 0, 0, m_sceneSize.height());
    lg.setColorAt(0.0, paletteColor(QPalette::Window, 50));
    lg.setColorAt(1.0, paletteColor(QPalette::Window, -60));

    // paint with good performance
    painter->setCompositionMode(QPainter::CompositionMode_Source);
    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->fillRect(rect.toAlignedRect(), lg);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
}


/// Dynamic Size Logic
void CoolbarScene::setDynamicSizeHint(const QSize & size)
{
    if (size != m_dynamicSizeHint) {
        m_dynamicSizeHint = size;
        emit shouldResizeView();
    }
}

bool CoolbarScene::updateDynamicSize(int testWidth)
{
    // recalc size mode and hint
    SizeMode prevMode = m_dynamicSizeMode;
    QSize targetSizeHint = m_dynamicSizeHint;
    if (testWidth > 500 || testWidth == -1) {
        m_dynamicSizeMode = DesktopSize;
        targetSizeHint = QSize(400, 100);
    } else if (testWidth > 320) {
        m_dynamicSizeMode = NetbookSize;
        targetSizeHint = QSize(300, 60);
    } else {
        m_dynamicSizeMode = IDeviceSize;
        targetSizeHint = QSize(200, 40);
    }

    // if needed (shouldn't be) update the dynamic size hint
    bool changed = prevMode != m_dynamicSizeMode;
    if (testWidth == -1) {
        setDynamicSizeHint(targetSizeHint);
    } else if (changed) {
        if (m_animateResize)
            Coolbar::animateObjectProperty(this, "dynamicSizeHint", 500, targetSizeHint); // InOutCubic
        else
            setDynamicSizeHint(targetSizeHint);
    }

    // tell if changed
    return changed;
}
