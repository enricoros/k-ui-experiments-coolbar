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

#include "Amarok22Layouter.h"
#include "Coolbar/CoolbarAnimation.h"
#include "Coolbar/CoolbarElement.h"

void Amarok22Layouter::layout(const AmarokScene &scene, CoolbarScene::SizeMode mode)
{
    //QSizeF s;
    int left, top;

    // hide Visualization
    scene.visualization()->hide();
    scene.positionSlider()->hide();
    scene.tagInfo()->hide();
    scene.currentTime()->hide();
    scene.timeLeft()->hide();

    // hide flames
    scene.flame()->setVisible(false);

    // update buttons
    switch (mode) {
        default:
            top = scene.rect().center().y() - 54/2;
            left = 10;
            for (int b = 0; b < 4; b++) {
                Coolbar::animateObjectProperty(scene.button(b), "pos", 300, QPointF(left, top));
                Coolbar::animateObjectProperty(scene.button(b), "size", 500, QSizeF(54, 54));
                left += 42;
            }
            break;

        case CoolbarScene::IDeviceSize:
            left = scene.rect().center().x() - 2 * (32 + 4);
            top = scene.rect().center().y() - 32 / 2;
            for (int b = 0; b < 4; b++) {
                Coolbar::animateObjectProperty(scene.button(b), "size", 500, QSizeF(32, 32));
                Coolbar::animateObjectProperty(scene.button(b), "pos", 300, QPointF(left, top));
                left += 32 + 4;
            }
            break;
    }
}
