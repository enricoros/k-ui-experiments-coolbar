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

#include "CoolbarElement.h"
#include "CoolbarAnimation.h"
#include "CoolbarScene.h"
#include "CoolbarTheme.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QGraphicsSceneMouseEvent>


CoolbarElement::CoolbarElement(CoolbarScene * coolbarScene, QGraphicsItem * parent)
  : QGraphicsWidget(parent)
  , m_scene(coolbarScene)
  , m_hovered(false)
{
    // add to the scene and listen for changes
    m_scene->addItem(this);
    connect(m_scene, SIGNAL(themeChanged()), this, SLOT(themeChanged()));

    // customize item
    setAcceptHoverEvents(true);
    resize(10, 10);
}

CoolbarElement::~CoolbarElement()
{
    // nothing to do here...
}

QPropertyAnimation * CoolbarElement::animate(const char * property, int duration, const QVariant & endValue, const QVariant & startValue)
{
    QPropertyAnimation *anim = 0;
    AnimationMap::iterator i = m_animations.begin();
    while (i != m_animations.end())
    {
        if (i.key() == property)
        {
            if (!i.value().isNull())
                i.value().data()->stop();
            anim = Coolbar::animateObjectProperty(this, property, duration, endValue, startValue);
            i.value() = QWeakPointer<QPropertyAnimation>(anim);
            return anim;
        }
        else if (i.value().isNull())
            i = m_animations.erase(i);
        else
            ++i;
    }
    anim = Coolbar::animateObjectProperty(this, property, duration, endValue, startValue);
    m_animations.insert(QString(property), QWeakPointer<QPropertyAnimation>(anim));
    return anim;
}

void CoolbarElement::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // default filling for unpainted subclasses
    painter->fillRect(rect(), Qt::red);
}

void CoolbarElement::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    m_hovered = true;
    update();
}

void CoolbarElement::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    m_hovered = false;
    update();
}

void CoolbarElement::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();
}

CoolbarScene * CoolbarElement::scene() const
{
    return m_scene;
}

CoolbarTheme * CoolbarElement::theme() const
{
    return m_scene->theme();
}
