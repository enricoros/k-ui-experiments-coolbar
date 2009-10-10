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
#include "CoolbarScene.h"
#include "CoolbarTheme.h"

CoolbarElement::CoolbarElement(QGraphicsItem * parent)
  : QGraphicsWidget(parent)
{
    // nothing to do here...
}

CoolbarElement::~CoolbarElement()
{
    // nothing to do here...
}

CoolbarScene * CoolbarElement::scene() const
{
    return dynamic_cast<CoolbarScene *>(QGraphicsWidget::scene());
}

CoolbarTheme * CoolbarElement::theme() const
{
    CoolbarScene * scene = dynamic_cast<CoolbarScene *>(QGraphicsWidget::scene());
    return scene ? scene->theme() : 0;
}
