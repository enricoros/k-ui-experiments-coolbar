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
#include "ButtonElement.h"
#include "FlameElement.h"
#include "VisualizationElement.h"

void Amarok22Layouter::layout(
        const QRectF & rect,
        CoolbarScene::SizeMode mode,
        ButtonElement * buttons[4],
        FlameElement * flame,
        VisualizationElement * visualization )
{
    //QSizeF s;
    int left, top;

    // hide Visualization
    visualization->hide();

    // hide flames
    flame->setVisible(false);

    // update buttons
    switch (mode) {
        default:
            top = rect.center().y() - 54/2;
            left = 10;
            for (int b = 0; b < 4; b++) {
                Coolbar::animateObjectProperty(buttons[b], "pos", 300, QPointF(left, top));
                Coolbar::animateObjectProperty(buttons[b], "size", 500, QSizeF(54, 54));
                left += 42;
            }
            break;

        case CoolbarScene::IDeviceSize:
            left = rect.center().x() - 2 * (32 + 4);
            top = rect.center().y() - 32 / 2;
            for (int b = 0; b < 4; b++) {
                Coolbar::animateObjectProperty(buttons[b], "size", 500, QSizeF(32, 32));
                Coolbar::animateObjectProperty(buttons[b], "pos", 300, QPointF(left, top));
                left += 32 + 4;
            }
            break;
    }
}
