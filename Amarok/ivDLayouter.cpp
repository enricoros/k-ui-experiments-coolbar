/***************************************************************************
 *                                                                         *
 *   This file is part of the Coolbar project,                             *
 *       http://www.gitorious.org/qt4-gadgets/coolbar                      *
 *                                                                         *
 *   Copyright (C) 2009 by Thomas Luebking <thomas.luebking@web.de>        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "ivDLayouter.h"
#include "Coolbar/CoolbarAnimation.h"
#include "Coolbar/CoolbarElement.h"

void ivDLayouter::layout(const AmarokScene &scene, CoolbarScene::SizeMode mode)
{
    const QRectF rect = scene.rect();
    qreal left;
    qreal top = (mode == CoolbarScene::IDeviceSize) ? 4 : 6;
    qreal h = (mode == CoolbarScene::DesktopSize) ? 10.0*rect.height()/16.0 : rect.height() - 2 * top;
    qreal aw, sw;

    // update Visualization
    ///NOTICE 512/768 shall be dependent on screen width as well
    scene.visualization()->setZValue(-1);
    scene.visualization()->show();
    scene.positionSlider()->setVisible(scene.isUnderMouse() || mode == CoolbarScene::DesktopSize);
    scene.currentTime()->setOpacity(0);
    scene.timeLeft()->setOpacity(0);

    scene.tagInfo()->show();
    scene.currentTime()->show();
    scene.timeLeft()->show();
    
    if (rect.width() < 512)
        sw = aw = rect.width() - 6;
    else if (rect.width() < 768)
        sw = aw = 0.618*rect.width();
    else
    {
        aw = 0.382*rect.width();
        sw = 0.618*rect.width();
    }

    left = rect.center().x() - aw / 2;
    
    scene.visualization()->animate("size", 500, QSizeF(aw,h));
    scene.visualization()->animate("pos", 300, QPointF(left, top));

    scene.tagInfo()->animate("size", 500, QSizeF(aw,h));
    scene.tagInfo()->animate("pos", 300, QPointF(left, top));

    if (mode == CoolbarScene::DesktopSize)
    {
        if (aw != sw)
            left = rect.center().x() - sw / 2;
        scene.currentTime()->animate("size", 500, QSizeF(sw/3.0,h));
        scene.currentTime()->animate("pos", 300, QPointF(left, top));
        scene.timeLeft()->animate("size", 500, QSizeF(sw/3.0,h));
        scene.timeLeft()->animate("pos", 300, QPointF(left+2*sw/3.0, top));
    }
//     Coolbar::animateObjectProperty(visualization, "colorness", 2000, 0.0);

    // update buttons
    left = rect.center().x() - 2 * (h + top);
    for (int b = 0; b < 4; b++) {
        scene.button(b)->animate("size", 500, QSizeF(h, h));
        scene.button(b)->animate("pos", 300, QPointF(left, top));
        left += h + top;
    }

    // update slider
    left = rect.center().x() - sw / 2;
    if (mode == CoolbarScene::DesktopSize)
    {
        h = rect.bottom() - (4*top + h);
        top = rect.bottom() - (top + h);
    }
    else if (mode == CoolbarScene::NetbookSize)
    {
        h = rect.height()/3.0;
        top = rect.top() + h;
    }
    else
    {
        h = rect.height()/2.0;
        top = rect.top() + h/2.0;
    }
    scene.positionSlider()->animate("size", 500, QSizeF(sw,h));
    scene.positionSlider()->animate("pos", 300, QPointF(left, top));
    if (mode != CoolbarScene::DesktopSize)
    {
        scene.currentTime()->animate("size", 500, QSizeF(sw/3.0,h));
        scene.currentTime()->animate("pos", 300, QPointF(left+4, top));
        scene.timeLeft()->animate("size", 500, QSizeF(sw/3.0,h));
        scene.timeLeft()->animate("pos", 300, QPointF(left+2*sw/3.0-4, top));
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

void ivDLayouter::event(QEvent::Type type, void * item, const AmarokScene &scene, CoolbarScene::SizeMode mode)
{
    switch (type)
    {
        case QEvent::Enter:
        case QEvent::Leave:
            if (item == &scene)
                sceneHovered(type == QEvent::Enter, scene, mode);
            else if (item == scene.positionSlider())
                sliderHovered(type == QEvent::Enter, scene, mode);
            break;
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
            if (item == scene.positionSlider())
                sliderClicked(type == QEvent::MouseButtonPress, scene, mode);
            break;
        default:
            break;
    }
}

void ivDLayouter::sceneHovered(bool hovered, const AmarokScene &scene, CoolbarScene::SizeMode mode)
{
    if (mode != CoolbarScene::DesktopSize)
        scene.positionSlider()->setVisible(hovered);
//     qreal vOpacity;
    if (mode == CoolbarScene::DesktopSize)
        scene.positionSlider()->animate("opacity", 500, 1.0);
    else
        scene.positionSlider()->animate("opacity", 500, 0.15);

    scene.visualization()->animate("opacity", 500, 1.0-hovered*0.85);
    scene.tagInfo()->animate("opacity", 300, !hovered);
    for (int b = 0; b < 4; b++)
    {
        scene.button(b)->setZValue(hovered);
        scene.button(b)->animate("opacity", 500-300*hovered, hovered);
    }
}

void ivDLayouter::sliderClicked(bool down, const AmarokScene &scene, CoolbarScene::SizeMode mode)
{
    scene.currentTime()->animate("opacity", 150, down);
    scene.timeLeft()->animate("opacity", 150, down);
    if (mode == CoolbarScene::DesktopSize)
    {
        for (int b = 0; b < 4; b++)
            scene.button(b)->animate("opacity", 150, !down);
    }
}

void ivDLayouter::sliderHovered(bool hovered, const AmarokScene &scene, CoolbarScene::SizeMode mode)
{
    if (mode == CoolbarScene::DesktopSize || !scene.isUnderMouse())
        return;
    qreal opacity = 1.0-!hovered*0.85;
    scene.positionSlider()->setZValue(2*hovered);
    scene.positionSlider()->animate("opacity", 250, opacity);
    opacity = 1.0-hovered*0.85;
    for (int b = 0; b < 4; b++)
        scene.button(b)->animate("opacity", 250, opacity);
}
