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

#include "ProposedLayouter.h"
#include "Coolbar/CoolbarAnimation.h"
#include "Coolbar/CoolbarElement.h"

void ProposedLayouter::layout(const AmarokScene &scene, CoolbarScene::SizeMode mode)
{
    const QRectF &rect = scene.rect();
    QSizeF s;
    int left, top;

    scene.positionSlider()->hide();
    scene.tagInfo()->hide();
    scene.currentTime()->hide();
    scene.timeLeft()->hide();
    
    // update Visualization
    scene.visualization()->show();
    switch (mode) {
        default:
            s = QSizeF(4 * rect.width() / 10, rect.height() / 2);
            if (mode == CoolbarScene::DesktopSize) {
                left = rect.center().x() - s.width() / 2;
                top = rect.bottom() - s.height();
            } else {
                left = rect.width() - (s.width() + 10);
                top = rect.center().y() - s.height() / 3;
            }
            Coolbar::animateObjectProperty(scene.visualization(), "size", 500, s);
            Coolbar::animateObjectProperty(scene.visualization(), "pos", 300, QPointF(left, top));
            Coolbar::animateObjectProperty(scene.visualization(), "colorness", 2000, 0.0);
            break;
        case CoolbarScene::IDeviceSize:
            Coolbar::animateObjectProperty(scene.visualization(), "size", 500, rect.size());
            Coolbar::animateObjectProperty(scene.visualization(), "pos", 300, QPointF(0, 0));
            Coolbar::animateObjectProperty(scene.visualization(), "colorness", 2000, 1.0);
            break;
    }

    // update buttons
    switch (mode) {
        case CoolbarScene::DesktopSize:
            top = 0;
            left = rect.center().x() - 2 * (64 + 4);
            for (int b = 0; b < 4; b++) {
                Coolbar::animateObjectProperty(scene.button(b), "pos", 300, QPointF(left, top));
                Coolbar::animateObjectProperty(scene.button(b), "size", 500, QSizeF(64, 64));
                left += 64 + 4;
            }
            break;

        default:
            left = rect.center().x() - 2 * (32 + 4);
            if (mode == CoolbarScene::NetbookSize)
                left = 10;
            top = rect.center().y() - 32 / 2;
            for (int b = 0; b < 4; b++) {
                Coolbar::animateObjectProperty(scene.button(b), "size", 500, QSizeF(32, 32));
                Coolbar::animateObjectProperty(scene.button(b), "pos", 300, QPointF(left, top));
                left += 32 + 4;
            }
            break;
    }

    // update flames
    scene.flame()->show();
    s = QSizeF(rect.width() / 2, 2 * rect.height() / 3);
    if (mode == CoolbarScene::DesktopSize)
        top = rect.height() - 2 * s.height() / 3;
    else
        top = (rect.height() - s.height()) / 2;
    scene.flame()->setVisible(mode != CoolbarScene::IDeviceSize);
    Coolbar::animateObjectProperty(scene.flame(), "size", 500, s);
    Coolbar::animateObjectProperty(scene.flame(), "pos", 300, QPointF(0, top));
}
