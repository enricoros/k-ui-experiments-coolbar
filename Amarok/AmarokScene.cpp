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
#include "SliderElement.h"
#include "LabelElement.h"
#include "Coolbar/CoolbarAnimation.h"
#include "Coolbar/CoolbarTheme.h"

// dummy auto progress
#include <QTimer>
static int _currentTime = 0;

#include <QtDebug>
AmarokScene::AmarokScene(QObject * parent)
  : CoolbarScene(parent)
  , m_layouter(0)
  , m_animateLayouting(true)
  , m_visualizationIndex(-1)
  , m_trackLength(1)
  , m_visualization(0)
  , m_positionSlider(0)
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

    setTrackLength(9*60+14);
    
    m_positionSlider = new SliderElement(this);
    connect (m_positionSlider, SIGNAL(valueChanged(qreal)), this, SLOT(slotPositionSliderChanged(qreal)));
    m_tagInfo = new LabelElement(this);
    m_tagInfo->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    m_tagInfo->setMaxPointSize( 14.0 );
    m_tagInfo->setContent(QStringList() << "Why so serious?" << "The Dark Knight (2008)" << "Hans Zimmer" << "9:14");
    m_currentTime = new LabelElement(this);
    m_currentTime->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    m_currentTime->setMaxPointSize( 24.0 );
    m_timeLeft = new LabelElement(this);
    m_timeLeft->setAlignment(Qt::AlignRight|Qt::AlignBottom);
    m_timeLeft->setMaxPointSize( 24.0 );

    // dummy autoprogress
    QTimer *t = new QTimer(this);
    connect (t, SIGNAL(timeout()), this, SLOT(setCurrentTime()));
    t->start(1000);
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
        m_layouter->event(m_underMouse ? QEvent::Enter : QEvent::Leave, this, *this, dynamicSizeMode());
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


static QString timeStringFromSecs(int secs, int max)
{
    QString ret;
    if (secs < 0 || secs > max)
        return ret;
    if (max > 3600)
    {
        if (const int h = secs / 3600)
        {
            if (max > 36000 && h < 10)
                ret += "0";
            ret += QString::number(h) + ":";
            secs -= 3600*h;
        }
        else
            ret += "00:";
    }
    if (max > 60)
    {
        if (const int m = secs / 60)
        {
            if (m < 10)
                ret += "0";
            ret += QString::number(m) + ":";
            secs -= 60*m;
        }
        else
            ret += "00:";
    }
    if (secs < 10)
        ret += "0";
    ret += QString::number(secs);
    return ret;
}

// dummy...
void AmarokScene::setCurrentTime()
{
    ++_currentTime;
    _currentTime %= m_trackLength;
    setCurrentTime(_currentTime);
}

void AmarokScene::setCurrentTime(int sec)
{
    // dummy, to keep slider and autoprogress in sync
    _currentTime = sec;
    // ------
    m_positionSlider->blockSignals(true);
    m_positionSlider->setValue((qreal)sec / m_trackLength);
    m_positionSlider->blockSignals(false);
    m_currentTime->setContent(QStringList() << timeStringFromSecs(sec, m_trackLength));
    m_timeLeft->setContent(QStringList() << timeStringFromSecs(m_trackLength - sec, m_trackLength));
}

void AmarokScene::slotPositionSliderChanged(qreal percent)
{
    setCurrentTime(qRound(percent * m_trackLength));
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
        m_layouter->event(m_underMouse ? QEvent::Enter : QEvent::Leave, this, *this, dynamicSizeMode());
}

bool AmarokScene::event(QEvent * ev)
{
    switch (ev->type())
    {
        case QEvent::Enter:
        case QEvent::Leave:
            m_underMouse = (ev->type() == QEvent::Enter);
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
            if (m_layouter)
                m_layouter->event(ev->type(), this, *this, dynamicSizeMode());
            break;
        default:
            break;
    }
    return CoolbarScene::event(ev);
}

void AmarokScene::propagateEvent(void *element, QEvent::Type type)
{
    if (m_layouter)
        m_layouter->event(type, element, *this, dynamicSizeMode());
}
