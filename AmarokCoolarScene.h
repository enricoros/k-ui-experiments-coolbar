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

#ifndef AMAROKCOOLARSCENE_H
#define AMAROKCOOLARSCENE_H

#include "CoolarScene.h"

/// Amarok Specific Methods
class AmarokCoolarScene : public CoolarScene
{
    Q_OBJECT
    public:
        AmarokCoolarScene(QObject * parent = 0);

    protected:
        // ::CoolarScene
        void updateElementsLayout(const QRectF & newBounds);

    private:
};

#endif
