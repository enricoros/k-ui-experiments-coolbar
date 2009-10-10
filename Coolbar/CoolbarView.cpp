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

#include "CoolbarView.h"

#include "CoolbarScene.h"

#include <QResizeEvent>

CoolbarView::CoolbarView(CoolbarScene * coolbarScene, QWidget * parent)
  : QGraphicsView(parent)
  , m_coolbarScene(coolbarScene)
{
    // link to the scene
    setScene(m_coolbarScene);
    connect(m_coolbarScene, SIGNAL(shouldResizeView()), this, SLOT(slotResizeView()));

    // size policy: it needs to obey the vertical size hint
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    // customize appearance
    setFrameStyle(QFrame::NoFrame);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void CoolbarView::resizeEvent(QResizeEvent * event)
{
    m_coolbarScene->resize(event->size());
}

QSize CoolbarView::sizeHint() const
{
    return m_coolbarScene->dynamicSizeHint();
}

QSize CoolbarView::minimumSizeHint() const
{
    // clear the minimum size hint of the graphicsview, to use the size policy
    return QSize();
}

void CoolbarView::slotResizeView()
{
    updateGeometry();
}
