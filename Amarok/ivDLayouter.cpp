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


void ivDLayouter::layout(const AmarokScene &scene, CoolbarScene::SizeMode mode)
{
    const QRectF rect = scene.rect();
    qreal left;
    qreal top = (mode == CoolbarScene::IDeviceSize) ? 4 : 6;
    qreal h = (mode == CoolbarScene::DesktopSize) ? 10.0*rect.height()/16.0 : rect.height() - 2 * top;
    qreal w;

    // update Visualization
    scene.visualization()->show();
    if (rect.width() < 512)
        w = rect.width();
    else if (rect.width() < 1024)
        w = 0.618*rect.width();
    else
        w = 0.382*rect.width();

    left = rect.center().x() - w / 2;
    
    Coolbar::animateObjectProperty(scene.visualization(), "size", 500, QSizeF(w,h));
    Coolbar::animateObjectProperty(scene.visualization(), "pos", 300, QPointF(left, top));
//     Coolbar::animateObjectProperty(visualization, "colorness", 2000, 0.0);

    // update buttons
    left = rect.center().x() - 2 * (h + top);
    for (int b = 0; b < ButtonElement::ButtonCount; b++) {
        Coolbar::animateObjectProperty(scene.button(b), "pos", 300, QPointF(left, top));
        Coolbar::animateObjectProperty(scene.button(b), "size", 500, QSizeF(h, h));
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

void ivDLayouter::updateUnderMouse(const AmarokScene &scene, CoolbarScene::SizeMode)
{
    const bool hovered = scene.isUnderMouse();
    scene.visualization()->setZValue(!hovered);
    Coolbar::animateObjectProperty(scene.visualization(), "opacity", 500, 1.0-hovered*0.85);
    for (int b = 0; b < ButtonElement::ButtonCount; b++)
    {
        scene.button(b)->setZValue(hovered);
        Coolbar::animateObjectProperty(scene.button(b), "opacity", 500-300*hovered, hovered);
    }
}
