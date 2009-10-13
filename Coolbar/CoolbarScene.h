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

#ifndef __CoolbarScene_h__
#define __CoolbarScene_h__

#include <QEvent>
#include <QGraphicsScene>
#include <QPalette>
#include <QSize>
class CoolbarTheme;

class CoolbarScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(QSize dynamicSizeHint READ dynamicSizeHint WRITE setDynamicSizeHint)
    public:
        CoolbarScene(QObject * parent = 0);
        virtual ~CoolbarScene();

        // Theme (Look) support
        void setTheme(CoolbarTheme * theme);
        CoolbarTheme * theme() const;

        // animation when changing SizeMode (ex: DesktopSize -> IDeviceSize)
        void setResizeAnimationEnabled(bool);
        inline bool resizeAnimationEnabled() const { return m_animateResize; }

        // sets the geometry of the contents (could change dynamic size too)
        void resize(const QSize & viewSize);

        // dynamic size change, used by the Coolbar view
        enum SizeMode { DesktopSize, NetbookSize, IDeviceSize };
        SizeMode dynamicSizeMode() const;
        QSize dynamicSizeHint() const;

        virtual void propagateEvent(void */*element*/, QEvent::Type) {} // = 0;?

    Q_SIGNALS:
        // emitted when the size hint changes
        void shouldResizeView();
        void themeChanged();

    protected:
        // to be inherited
        virtual void updateElementsLayout(const QRectF & /*boundingRect*/) {}

        // to be used
        inline QSize sceneSize() const { return m_sceneSize; }
        inline QRectF sceneRect() const { return m_sceneRect; }

        // ::QGraphicsScene
        void drawBackground(QPainter * painter, const QRectF & rect);

    private:
        void setDynamicSizeHint(const QSize & size);
        bool updateDynamicSize(int testWidth);

        // internal
        CoolbarTheme * m_theme;
        bool m_animateResize;

        // scene geometry
        QSize m_sceneSize;
        QRectF m_sceneRect;

        // dynamic size
        SizeMode m_dynamicSizeMode;
        QSize m_dynamicSizeHint;
};

#endif
