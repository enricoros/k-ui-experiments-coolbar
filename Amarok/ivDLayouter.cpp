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
#include "ButtonElement.h"
#include "FlameElement.h"
#include "VisualizationElement.h"
#include "SliderElement.h"
#include "LabelElement.h"


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
    scene.slider()->setVisible(scene.isUnderMouse() || mode == CoolbarScene::DesktopSize);
    scene.currentTime()->setOpacity(0);
    scene.timeLeft()->setOpacity(0);
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
    
    Coolbar::animateObjectProperty(scene.visualization(), "size", 500, QSizeF(aw,h));
    Coolbar::animateObjectProperty(scene.visualization(), "pos", 300, QPointF(left, top));

    Coolbar::animateObjectProperty(scene.tagInfo(), "size", 500, QSizeF(aw,h));
    Coolbar::animateObjectProperty(scene.tagInfo(), "pos", 300, QPointF(left, top));

    Coolbar::animateObjectProperty(scene.currentTime(), "size", 500, QSizeF(aw/3.0,h));
    Coolbar::animateObjectProperty(scene.currentTime(), "pos", 300, QPointF(left, top));
    Coolbar::animateObjectProperty(scene.timeLeft(), "size", 500, QSizeF(aw/3.0,h));
    Coolbar::animateObjectProperty(scene.timeLeft(), "pos", 300, QPointF(left+2*aw/3.0, top));
//     Coolbar::animateObjectProperty(visualization, "colorness", 2000, 0.0);

    // update buttons
    left = rect.center().x() - 2 * (h + top);
    for (int b = 0; b < ButtonElement::ButtonCount; b++) {
        Coolbar::animateObjectProperty(scene.button(b), "size", 500, QSizeF(h, h));
        Coolbar::animateObjectProperty(scene.button(b), "pos", 300, QPointF(left, top));
        left += h + top;
    }

    // update slider
    left = rect.center().x() - sw / 2;
    if (mode == CoolbarScene::DesktopSize)
    {
        h = rect.bottom() - (4*top + h);
        top = rect.bottom() - (top + h);
    }
    else
    {
        h = rect.height()/3.0;
        top = rect.top() + h;
    }
    Coolbar::animateObjectProperty(scene.slider(), "size", 500, QSizeF(sw,h));
    Coolbar::animateObjectProperty(scene.slider(), "pos", 300, QPointF(left, top));

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
            else if (item == scene.slider())
                sliderHovered(type == QEvent::Enter, scene, mode);
            break;
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
            if (item == scene.slider())
                sliderClicked(type == QEvent::MouseButtonPress, scene, mode);
            break;
        default:
            break;
    }
}

void ivDLayouter::sceneHovered(bool hovered, const AmarokScene &scene, CoolbarScene::SizeMode mode)
{
    if (mode != CoolbarScene::DesktopSize)
        scene.slider()->setVisible(hovered);
//     qreal vOpacity;
    if (mode == CoolbarScene::DesktopSize)
    {
        Coolbar::animateObjectProperty(scene.slider(), "opacity", 500, 1.0);
    }
    else
    {
        Coolbar::animateObjectProperty(scene.slider(), "opacity", 500, 0.15);
    }
    Coolbar::animateObjectProperty(scene.visualization(), "opacity", 500, 1.0-hovered*0.85);
    Coolbar::animateObjectProperty(scene.tagInfo(), "opacity", 300, !hovered);
    for (int b = 0; b < ButtonElement::ButtonCount; b++)
    {
        scene.button(b)->setZValue(hovered);
        Coolbar::animateObjectProperty(scene.button(b), "opacity", 500-300*hovered, hovered);
    }
}

void ivDLayouter::sliderClicked(bool down, const AmarokScene &scene, CoolbarScene::SizeMode mode)
{
    Coolbar::animateObjectProperty(scene.currentTime(), "opacity", 150, down);
    Coolbar::animateObjectProperty(scene.timeLeft(), "opacity", 150, down);
    for (int b = 0; b < ButtonElement::ButtonCount; b++)
        Coolbar::animateObjectProperty(scene.button(b), "opacity", 150, !down);
}

void ivDLayouter::sliderHovered(bool hovered, const AmarokScene &scene, CoolbarScene::SizeMode mode)
{
    if (mode == CoolbarScene::DesktopSize)
        return;
    qreal opacity = 1.0-!hovered*0.85;
    scene.slider()->setZValue(2*hovered);
    Coolbar::animateObjectProperty(scene.slider(), "opacity", 250, opacity);
    opacity = 1.0-hovered*0.85;
    for (int b = 0; b < ButtonElement::ButtonCount; b++)
        Coolbar::animateObjectProperty(scene.button(b), "opacity", 250, opacity);
}
