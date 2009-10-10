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

#include "ButtonElement.h"
#include "Coolbar/CoolbarTheme.h"
#include "AmarokScene.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

ButtonElement::ButtonElement(ButtonType type, CoolbarScene * scene, QGraphicsItem * parent)
  : CoolbarElement(scene, parent)
  , m_buttonType(type)
{
    // customize item
    setZValue(0.0);

    // load initial pixmap
    themeChanged();
}

void ButtonElement::themeChanged()
{
    if (CoolbarTheme * t = theme()) {
        switch (m_buttonType) {
            case PlayButton:    m_pixmap = t->elementPixmap("playButton");  break;
            case PauseButton:   m_pixmap = t->elementPixmap("pauseButton");  break;
            case StopButton:    m_pixmap = t->elementPixmap("stopButton");  break;
            case PrevButton:    m_pixmap = t->elementPixmap("prevButton");  break;
            case NextButton:    m_pixmap = t->elementPixmap("nextButton");  break;
        }
        if (size().isEmpty() && !m_pixmap.isNull())
            resize(m_pixmap.size());
    }
}

void ButtonElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setOpacity(isHovered() ? 1.0 : 0.4);
    painter->drawPixmap(rect().toAlignedRect(), m_pixmap);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
}
