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

#include "TestWindow.h"
#include "ui_TestWindow.h"

#include "AmarokCoolarScene.h"
#include "CoolarView.h"

TestWindow::TestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);

    // create and use Coolar Scene and View
    AmarokCoolarScene * aScene = new AmarokCoolarScene;
    CoolarView * coolar = new CoolarView(aScene);
    ui->containerLayout->addWidget(coolar);
}

TestWindow::~TestWindow()
{
    delete ui;
}
