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

#include "CoolbarAnimation.h"

#if QT_VERSION >= 0x040600
#include <QPropertyAnimation>
#endif

QPropertyAnimation * Coolbar::animateObjectProperty(QObject * object, const char * propName, int duration, const QVariant & endValue, const QVariant & startValue)
{
#if QT_VERSION >= 0x040600
    QPropertyAnimation * ani = new QPropertyAnimation(object, propName, object);
    ani->setEasingCurve(QEasingCurve::OutCubic);
    ani->setDuration(duration);
    if (startValue.isValid())
        ani->setStartValue(startValue);
    ani->setEndValue(endValue);
    ani->start(QPropertyAnimation::DeleteWhenStopped);
#else
    Q_UNUSED(duration);
    Q_UNUSED(startValue);
    object->setProperty(propName, endValue);
#endif
    return ani;
}

bool Coolbar::canAnimate()
{
#if QT_VERSION >= 0x040600
    return true;
#else
    return false;
#endif
}
