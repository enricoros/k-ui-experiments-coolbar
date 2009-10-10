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
#include "ButtonElement.h"
#include "FlameElement.h"
#include "VisualizationElement.h"


void ProposedLayouter::layout(
        const QRectF & rect,
        CoolbarScene::SizeMode mode,
        ButtonElement * buttons[4],
        FlameElement * flame,
        VisualizationElement * visualization)
{
    QSizeF s;
    int left, top;

    // update Visualization
    visualization->show();
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
            Coolbar::animateObjectProperty(visualization, "size", 500, s);
            Coolbar::animateObjectProperty(visualization, "pos", 300, QPointF(left, top));
            Coolbar::animateObjectProperty(visualization, "colorness", 2000, 0.0);
            break;
        case CoolbarScene::IDeviceSize:
            Coolbar::animateObjectProperty(visualization, "size", 500, rect.size());
            Coolbar::animateObjectProperty(visualization, "pos", 300, QPointF(0, 0));
            Coolbar::animateObjectProperty(visualization, "colorness", 2000, 1.0);
            break;
    }

    // update buttons
    switch (mode) {
        case CoolbarScene::DesktopSize:
            top = 0;
            left = rect.center().x() - 2 * (64 + 4);
            for (int b = 0; b < 4; b++) {
                Coolbar::animateObjectProperty(buttons[b], "pos", 300, QPointF(left, top));
                Coolbar::animateObjectProperty(buttons[b], "size", 500, QSizeF(64, 64));
                left += 64 + 4;
            }
            break;

        default:
            left = rect.center().x() - 2 * (32 + 4);
            if (mode == CoolbarScene::NetbookSize)
                left = 10;
            top = rect.center().y() - 32 / 2;
            for (int b = 0; b < 4; b++) {
                Coolbar::animateObjectProperty(buttons[b], "size", 500, QSizeF(32, 32));
                Coolbar::animateObjectProperty(buttons[b], "pos", 300, QPointF(left, top));
                left += 32 + 4;
            }
            break;
    }

    // update flames
    flame->show();
    s = QSizeF(rect.width() / 2, 2 * rect.height() / 3);
    if (mode == CoolbarScene::DesktopSize)
        top = rect.height() - 2 * s.height() / 3;
    else
        top = (rect.height() - s.height()) / 2;
    flame->setVisible(mode != CoolbarScene::IDeviceSize);
    Coolbar::animateObjectProperty(flame, "size", 500, s);
    Coolbar::animateObjectProperty(flame, "pos", 300, QPointF(0, top));
}
