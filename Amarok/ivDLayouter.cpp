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

#include "ivDLayouter.h"
#include "Coolbar/CoolbarAnimation.h"
#include "ButtonElement.h"
#include "FlameElement.h"
#include "VisualizationElement.h"


void ivDLayouter::layout(
        const QRectF & rect,
        CoolbarScene::SizeMode mode,
        ButtonElement * buttons[4],
        FlameElement * flame,
        VisualizationElement * visualization)
{
    qreal left;
    qreal top = (mode == CoolbarScene::IDeviceSize) ? 4 : 6;
    qreal h = (mode == CoolbarScene::DesktopSize) ? 10.0*rect.height()/16.0 : rect.height() - 2 * top;
    qreal w;

    // update Visualization
    visualization->show();
    if (rect.width() < 512)
        w = rect.width();
    else if (rect.width() < 1024)
        w = 0.618*rect.width();
    else
        w = 0.382*rect.width();

    left = rect.center().x() - w / 2;
    
    Coolbar::animateObjectProperty(visualization, "size", 500, QSizeF(w,h));
    Coolbar::animateObjectProperty(visualization, "pos", 300, QPointF(left, top));
//     Coolbar::animateObjectProperty(visualization, "colorness", 2000, 0.0);

    // update buttons
    left = rect.center().x() - 2 * (h + top);
    for (int b = 0; b < 4; b++) {
        Coolbar::animateObjectProperty(buttons[b], "pos", 300, QPointF(left, top));
        Coolbar::animateObjectProperty(buttons[b], "size", 500, QSizeF(h, h));
        left += h + top;
    }

//     // update flames
//     flame->show();
//     s = QSizeF(rect.width() / 2, 2 * rect.height() / 3);
//     if (mode == CoolbarScene::DesktopSize)
//         top = rect.height() - 2 * s.height() / 3;
//     else
//         top = (rect.height() - s.height()) / 2;
//     flame->setVisible(mode != CoolbarScene::IDeviceSize);
//     Coolbar::animateObjectProperty(flame, "size", 500, s);
//     Coolbar::animateObjectProperty(flame, "pos", 300, QPointF(0, top));
}

void ivDLayouter::enterEvent(ButtonElement * buttons[4], VisualizationElement *visualization)
{
    visualization->setZValue(0);
    Coolbar::animateObjectProperty(visualization, "opacity", 500, 0.2);
    for (int b = 0; b < 4; b++)
    {
        buttons[b]->setZValue(1);
        Coolbar::animateObjectProperty(buttons[b], "opacity", 200, 1.0);
    }
}

void ivDLayouter::leaveEvent(ButtonElement * buttons[4], VisualizationElement *visualization)
{
    Coolbar::animateObjectProperty(visualization, "opacity", 300, 1.0);
    visualization->setZValue(1);
    for (int b = 0; b < 4; b++)
    {
        buttons[b]->setZValue(0);
        Coolbar::animateObjectProperty(buttons[b], "opacity", 500, 0.0);
    }
}
