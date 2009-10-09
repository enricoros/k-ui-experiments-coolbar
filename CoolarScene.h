/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2009-2009 by Enrico Ros <enrico.ros@gmail.com>        *
 *   Started on 9 Oct 2009 by root.
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef COOLARSCENE_H
#define COOLARSCENE_H

#include <QGraphicsScene>
#include <QPalette>
#include <QSize>

class CoolarScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(QSize dynamicSizeHint READ dynamicSizeHint WRITE setDynamicSizeHint)
    public:
        CoolarScene(QObject * parent = 0);

        // sets the geometry of the contents (could change dynamic size too)
        void resize(const QSize & viewSize);

        // dynamic size change, used by the Coolar view
        enum SizeMode { DesktopSize, NetbookSize, IDeviceSize };
        SizeMode dynamicSizeMode() const;
        QSize dynamicSizeHint() const;

    Q_SIGNALS:
        // emitted when the size hint changes
        void shouldResizeView();

    protected:
        // to be inherited
        virtual void updateElementsLayout(const QRectF & /*boundingRect*/) {}

        // to be used
        inline QSize sceneSize() const { return m_sceneSize; }
        inline QRectF sceneRect() const { return m_sceneRect; }
        QColor paletteColor(QPalette::ColorRole role, int lightAdj = 0);

        // ::QGraphicsScene
        void drawBackground(QPainter * painter, const QRectF & rect);

    private:
        void setDynamicSizeHint(const QSize & size);
        bool updateDynamicSize(int testWidth);

        // scene geometry
        QSize m_sceneSize;
        QRectF m_sceneRect;

        // dynamic size
        SizeMode m_dynamicSizeMode;
        QSize m_dynamicSizeHint;
};

#endif
