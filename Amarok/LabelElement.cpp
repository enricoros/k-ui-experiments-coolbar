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

#include "LabelElement.h"

#include "Coolbar/CoolbarAnimation.h"
#include "Coolbar/CoolbarScene.h"
#include <QAbstractAnimation>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPainter>

#define TOGGLE(_BOOL_) _BOOL_ = !_BOOL_

static const int DT = 4000; // display duration
static const int FT = 500; // fade duration > 50!!!!

LabelElement::LabelElement(CoolbarScene * scene, QGraphicsItem * parent)
: CoolbarElement(scene, parent)
, m_time(0)
, m_index(0)
, m_animTimer(0)
, m_maxPixelSize(0)
, m_maxPointSize(0.0)
, m_opacity(1.0)
, m_animated(true)
, m_align(Qt::AlignCenter)
, m_buffer(0)
{}

void LabelElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!m_buffer || m_content.isEmpty())
        return;
    qreal left = (m_align & Qt::AlignLeft) ? 0.0 : rect().width() - m_buffer->width();
    if (m_align & Qt::AlignHCenter)
        left /= 2.0;
    qreal top = (m_align & Qt::AlignTop) ? 0.0 : rect().height() - m_buffer->height();
    if (m_align & Qt::AlignVCenter)
        top /= 2.0;
    painter->setOpacity(m_opacity * opacity());
    painter->drawPixmap(QPointF(left, top), *m_buffer);
    painter->setOpacity(opacity());
}

void LabelElement::changeEvent(QEvent *ev)
{
    if (ev->type() == QEvent::PaletteChange)
        updateBuffer();
    else if (ev->type() == QEvent::FontChange || ev->type() == QEvent::LayoutDirectionChange)
        updatePath();
    CoolbarElement::changeEvent(ev);
}

void LabelElement::mouseReleaseEvent(QGraphicsSceneMouseEvent *me)
{
    if (me->button() == Qt::LeftButton)
    {
        TOGGLE(m_animated);
        if (m_animated)
        {
            if (m_content.count() > 1)
            {
                m_animTimer = startTimer(50);
                update();
            }
        }
        else if (m_animTimer)
        {
            killTimer(m_animTimer);
            m_animTimer = 0;
            update();
        }
    }
}

void LabelElement::rotateContent(bool fwd)
{
    if (m_content.count() < 2)
        return;
    if (fwd)
    {
        ++m_index;
        if (m_index >= m_content.count())
            m_index = 0;
    }
    else
    {
        --m_index;
        if (m_index < 0)
            m_index = m_content.count() - 1;
    }
    updatePath();
    update();
}

void LabelElement::setAlignment(Qt::Alignment a)
{
    m_align = a;
    updatePath();
}

void LabelElement::setContent(const QStringList &content, bool upd)
{
    if (content == m_content)
        return;
    m_content = content;
    m_time = 0;
    m_index = 0;
    if (m_content.count() > 1 && m_animated)
    {
        if (!m_animTimer)
            m_animTimer = startTimer(50);
    }
    else if (m_animTimer)
    {
        killTimer(m_animTimer);
        m_animTimer = 0;
        m_opacity = 1.0;
    }
    updatePath();
    if (upd && !m_animTimer)
        update();
}

void LabelElement::setMaxPixelSize(int s)
{
    m_maxPixelSize = s;
    updatePath();
}

void LabelElement::setMaxPointSize(qreal s)
{
    m_maxPointSize = s;
    updatePath();
}

void LabelElement::resizeEvent(QGraphicsSceneResizeEvent *ev)
{
    updatePath();
    CoolbarElement::resizeEvent(ev);
}

void LabelElement::timerEvent( QTimerEvent * te )
{
    if (!isVisible() || te->timerId() != m_animTimer)
        return;

    int level = -1.0;
    if (m_time < FT/50)
        level = m_time;
    else if (m_time > (DT-FT)/50)
        level = DT/50 - m_time;
    if (level > -1)
    {
        m_opacity = level; m_opacity /= (FT/50);
    }
    else
        m_opacity = 1.0;

    ++m_time;
    if (m_time > DT/50)
    {
        m_time = 0;
        rotateContent();
    }
}

void LabelElement::updateBuffer()
{
    QRect r = m_path.boundingRect().toAlignedRect();
    if (!m_buffer || m_buffer->size() != r.size())
    {
        delete m_buffer;
        m_buffer = new QPixmap(r.size());
    }
    m_buffer->fill(Qt::transparent);
    QPainter p(m_buffer);
    p.setRenderHint(QPainter::Antialiasing);
    p.translate(-r.topLeft());
    QColor textColor = Qt::white;
    QColor outline(70,70,70);
    p.setBrush(textColor);
    p.setPen(outline);
    p.drawPath(m_path);
    p.end();
}

void LabelElement::updatePath()
{
    if (m_content.isEmpty())
        return;
    // calculate font size
    const QString &text = m_content.at(m_index);
    QFont fnt = font();
    fnt.setBold(true);
    QSizeF sz = QFontMetricsF(fnt).size(0, text);
    const qreal f = qMin(rect().height()/sz.height(), rect().width()/sz.width());
    if (fnt.pointSize() > -1.0)
    {
        qreal s = fnt.pointSize()*f;
        if (m_maxPointSize > 0.0 && s > m_maxPointSize)
            s = m_maxPointSize;
        fnt.setPointSize(s);
    }
    else
    {
        int s = fnt.pixelSize()*f;
        if (m_maxPixelSize > 0 && s > m_maxPixelSize)
            s = m_maxPixelSize;
        fnt.setPixelSize(s);
    }
    QFontMetrics fm(fnt);
    sz = fm.size(0, text);
    m_path = QPainterPath();
    m_path.addText(0, 0, fnt, text);
    updateBuffer();
}

void LabelElement::wheelEvent(QGraphicsSceneWheelEvent * we)
{
    if (m_content.count() > 1)
        rotateContent(we->delta() < 0);
}
