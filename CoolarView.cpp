/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2009-2009 by Enrico Ros <enrico.ros@gmail.com>        *
 *   Started on 9 Oct 2009 by root.
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "CoolarView.h"

#include "CoolarScene.h"

#include <QResizeEvent>

CoolarView::CoolarView(CoolarScene * coolarScene, QWidget * parent)
  : QGraphicsView(parent)
  , m_coolarScene(coolarScene)
{
    // link to the scene
    setScene(m_coolarScene);
    connect(m_coolarScene, SIGNAL(shouldResizeView()), this, SLOT(slotResizeView()));

    // size policy: it needs to obey the vertical size hint
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    // customize appearance
    setFrameStyle(QFrame::NoFrame);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void CoolarView::resizeEvent(QResizeEvent * event)
{
    m_coolarScene->resize(event->size());
}

QSize CoolarView::sizeHint() const
{
    return m_coolarScene->dynamicSizeHint();
}

QSize CoolarView::minimumSizeHint() const
{
    // clear the minimum size hint of the graphicsview, to use the size policy
    return QSize();
}

void CoolarView::slotResizeView()
{
    updateGeometry();
}
