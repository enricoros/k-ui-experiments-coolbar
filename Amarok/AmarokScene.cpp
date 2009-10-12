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

#include "AmarokScene.h"
#include "ButtonElement.h"
#include "BarAnalyzerElement.h"
#include "DotAnalyzerElement.h"
#include "FlameElement.h"
#include "Coolbar/CoolbarAnimation.h"
#include "Coolbar/CoolbarTheme.h"


AmarokScene::AmarokScene(QObject * parent)
  : CoolbarScene(parent)
  , m_layouter(0)
  , m_animateLayouting(true)
  , m_visualizationIndex(-1)
  , m_visualization(0)
  , m_underMouse(false)
{
    // create flames
    m_flame = new FlameElement(this);

    // create buttons
    m_buttons[0] = new ButtonElement(ButtonElement::PrevButton, this);
    m_buttons[0]->setZValue(0.2);
    m_buttons[1] = new ButtonElement(ButtonElement::PlayButton, this);
    m_buttons[1]->setZValue(0.3);
    connect(m_buttons[1], SIGNAL(clicked()), m_flame, SLOT(pulse()));
    m_buttons[2] = new ButtonElement(ButtonElement::StopButton, this);
    m_buttons[2]->setZValue(0.2);
    m_buttons[3] = new ButtonElement(ButtonElement::NextButton, this);
    m_buttons[3]->setZValue(0.1);

    // create the Visualization
    slotNextVisualization();
}

AmarokScene::~AmarokScene()
{
    delete m_layouter;
}

void AmarokScene::setLayouter(Layouter * layouter)
{
    if (layouter != m_layouter) {
        // notify about the change
        Layouter * oldLayouter = m_layouter;
        m_layouter = layouter;
        emit layouterChanged();

        // update screen
        updateElementsLayout(sceneRect());
        m_layouter->updateUnderMouse(*this, dynamicSizeMode());
        update();

        // delete old
        delete oldLayouter;
    }
}

Layouter * AmarokScene::layouter() const
{
    return m_layouter;
}

void AmarokScene::setLayoutAnimationEnabled(bool on)
{
    if (on != m_animateLayouting)
        m_animateLayouting = on;
}

bool AmarokScene::layoutAnimationEnabled() const
{
    return m_animateLayouting;
}

void AmarokScene::setAnalyzerVisible(bool visible)
{
    m_visualization->setVisible(visible);
}

bool AmarokScene::analyzerVisible() const
{
    return m_visualization;
}

void AmarokScene::updateElementsLayout(const QRectF & bounds)
{
    // update base elements
    CoolbarScene::updateElementsLayout(bounds);

    // layout elements
    if (m_layouter) {
        m_layouter->layout(*this, dynamicSizeMode());
    }
}

void AmarokScene::slotNextVisualization()
{
    // backup params and delete previous visualization
    QPointF prevPos;
    QSizeF prevSize;
    if (m_visualization) {
        prevPos = m_visualization->pos();
        prevSize = m_visualization->size();
        delete m_visualization;
    }

    // change visualization
    if (++m_visualizationIndex >= 2)
        m_visualizationIndex = 0;
    switch (m_visualizationIndex) {
        case 0:
            m_visualization = new DotAnalyzerElement(this);
            break;
        case 1:
            m_visualization = new BarAnalyzerElement(this);
            break;
    }
    connect(m_visualization, SIGNAL(clicked()), this, SLOT(slotNextVisualization()), Qt::QueuedConnection);

    // restore params
    if (!prevSize.isNull()) {
        m_visualization->setPos(prevPos);
        m_visualization->resize(prevSize);
    }
    updateElementsLayout(sceneRect());
    if (m_layouter)
        m_layouter->updateUnderMouse(*this, dynamicSizeMode());
}

bool AmarokScene::event(QEvent * ev)
{
    if (ev->type() == QEvent::Enter || ev->type() == QEvent::Leave)
    {
        m_underMouse = (ev->type() == QEvent::Enter);
        if (m_layouter)
            m_layouter->updateUnderMouse(*this, dynamicSizeMode());
    }
    return CoolbarScene::event(ev);
}
