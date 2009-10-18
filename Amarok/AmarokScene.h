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

#ifndef __AmarokCoolbarScene_h__
#define __AmarokCoolbarScene_h__

#include "Coolbar/CoolbarScene.h"
class ButtonElement;
class VisualizationElement;
class FlameElement;
class SliderElement;
class LabelElement;
class AmarokScene;
class CoolbarElement;

/// Mandates behavior of a layouter
class Layouter
{
    public:
        virtual void event(QEvent::Type, void * /*item*/, const AmarokScene &, CoolbarScene::SizeMode) {}
        virtual void layout(const AmarokScene &, CoolbarScene::SizeMode) = 0;
        virtual QString layoutName() const = 0;
};

/// Amarok Specific Methods
class AmarokScene : public CoolbarScene
{
    Q_OBJECT
    public:
        AmarokScene(QObject * parent = 0);
        ~AmarokScene();

        // Layouters (Feel) support
        void setLayouter(Layouter * layouter);
        Layouter * layouter() const;

        // animate
        void setLayoutAnimationEnabled(bool);
        bool layoutAnimationEnabled() const;

        // TEMP show analyzers
        void setAnalyzerVisible(bool visible);
        bool analyzerVisible() const;

        inline CoolbarElement * button(int i) const { return (CoolbarElement*) m_buttons[i]; }
        inline CoolbarElement * flame() const { return (CoolbarElement*) m_flame; }
        inline CoolbarElement * visualization() const { return (CoolbarElement*) m_visualization; }
        inline CoolbarElement * positionSlider() const { return (CoolbarElement*) m_positionSlider; }
        inline CoolbarElement * tagInfo() const { return (CoolbarElement*) m_tagInfo; }
        inline CoolbarElement * currentTime() const { return (CoolbarElement*) m_currentTime; }
        inline CoolbarElement * timeLeft() const { return (CoolbarElement*) m_timeLeft; }
        inline CoolbarElement * volumeButton() const { return (CoolbarElement*) m_volumeButton; }
        inline CoolbarElement * volumeSlider() const { return (CoolbarElement*) m_volumeSlider; }

        inline bool isUnderMouse() const { return m_underMouse; }

        void propagateEvent(void *element, QEvent::Type type);

        void setTrackLength(int sec) { m_trackLength = sec; }

        inline QRectF rect() const { return CoolbarScene::sceneRect(); }

    Q_SIGNALS:
        void layouterChanged();

    public slots:
        void setCurrentTime(int sec);

    protected:
        /*virtual */bool event(QEvent * event);
        // ::CoolbarScene
        void updateElementsLayout(const QRectF & newBounds);

    private:
        // internal
        Layouter * m_layouter;
        bool m_animateLayouting;
        int m_visualizationIndex, m_trackLength;

        // elements
        ButtonElement * m_buttons[4], *m_volumeButton;
        FlameElement * m_flame;
        VisualizationElement * m_visualization;
        SliderElement * m_positionSlider, * m_volumeSlider;
        LabelElement *m_tagInfo, *m_currentTime, *m_timeLeft;

        bool m_underMouse;

    private Q_SLOTS:
        void slotNextVisualization();
        void slotPositionSliderDragged(qreal percent);
        // dummy slot for autoprogress
        void setCurrentTime();
};

#endif
