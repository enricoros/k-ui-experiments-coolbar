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

#ifndef __LabelElement_h__
#define __LabelElement_h__

#include "Amarok/VisualizationElement.h"
#include <QTimer>

class LabelElement : public CoolbarElement
{
    Q_OBJECT
//     Q_PROPERTY(qreal value READ value WRITE setValue)
    public:
        LabelElement(CoolbarScene *, QGraphicsItem * parent = 0);
        void setAlignment(Qt::Alignment a);
        inline Qt::Alignment alignment() { return m_align; }
        void setContent(const QStringList &content, bool upd = true);
        void setMaxPixelSize(int s);
        void setMaxPointSize(qreal s);

    protected:
        // ::QGraphicsItem
        void changeEvent(QEvent *);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
        void resizeEvent(QGraphicsSceneResizeEvent *);
        void timerEvent(QTimerEvent *);
        void wheelEvent(QGraphicsSceneWheelEvent *);

    private:
        void rotateContent(bool fwd = true);
        void updatePath();
        void updateBuffer();
    private:
        int m_time, m_index, m_animTimer, m_maxPixelSize;
        qreal m_maxPointSize, m_opacity;
        bool m_animated;
        QStringList m_content;
        QPainterPath m_path;
        Qt::Alignment m_align;
        QPixmap * m_buffer;
};

#endif
