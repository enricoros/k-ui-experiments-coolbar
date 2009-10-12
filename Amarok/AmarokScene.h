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
class AmarokScene;

/// Mandates behavior of a layouter
class Layouter
{
    public:
        virtual void updateUnderMouse(const AmarokScene &, CoolbarScene::SizeMode) {}
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

        inline ButtonElement * button(int i) const { return m_buttons[i]; }
        inline FlameElement * flame() const { return m_flame; }
        inline VisualizationElement * visualization() const { return m_visualization; }

        inline bool isUnderMouse() const { return m_underMouse; }

        inline QRectF rect() const { return CoolbarScene::sceneRect(); }

    Q_SIGNALS:
        void layouterChanged();

    protected:
        /*virtual */bool event(QEvent * event);
        // ::CoolbarScene
        void updateElementsLayout(const QRectF & newBounds);

    private:
        // internal
        Layouter * m_layouter;
        bool m_animateLayouting;
        int m_visualizationIndex;

        // elements
        ButtonElement * m_buttons[4];
        FlameElement * m_flame;
        VisualizationElement * m_visualization;

        bool m_underMouse;

    private Q_SLOTS:
        void slotNextVisualization();
};

#endif
