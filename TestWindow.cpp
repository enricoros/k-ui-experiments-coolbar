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
    m_acs = new AmarokCoolarScene;
    m_view = new CoolarView(m_acs);
    ui->containerLayout->addWidget(m_view);
    ui->aEq->setChecked(m_acs->equalizerVisible());
    ui->aSplit->setChecked(m_acs->buttonMode() == AmarokCoolarScene::SplittedButtons);
}

TestWindow::~TestWindow()
{
    delete ui;
}

void TestWindow::on_aEq_triggered(bool checked)
{
    m_acs->setEqualizerVisible(checked);
}

void TestWindow::on_aSplit_triggered(bool checked)
{
    m_acs->setButtonMode(checked ? AmarokCoolarScene::SplittedButtons : AmarokCoolarScene::VerticalStack);
}

void TestWindow::on_actionDesktop_Size_triggered()
{
    for (int i = 0; i < 10; i++) {
        resize(640, 100);
        qApp->processEvents();
    }
}

void TestWindow::on_actionNetbook_Size_triggered()
{
    for (int i = 0; i < 10; i++) {
        resize(400, 100);
        qApp->processEvents();
    }
}

void TestWindow::on_actionIStuff_Size_triggered()
{
    for (int i = 0; i < 10; i++) {
        resize(100, 100);
        qApp->processEvents();
    }
}
