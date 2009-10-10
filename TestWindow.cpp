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

#include "TestWindow.h"
#include "ui_TestWindow.h"

#include "Coolbar/CoolbarTheme.h"
#include "Coolbar/CoolbarView.h"
#include "AmarokScene.h"

TestWindow::TestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);

    // create and use Coolbar Scene and View
    m_amarokScene = new AmarokScene;
    m_view = new CoolbarView(m_amarokScene);
    ui->containerLayout->addWidget(m_view);
    ui->aEq->setChecked(m_amarokScene->equalizerVisible());
    ui->aSplit->setChecked(m_amarokScene->buttonMode() == AmarokScene::SplittedButtons);
}

TestWindow::~TestWindow()
{
    delete ui;
}

void TestWindow::on_aEq_triggered(bool checked)
{
    m_amarokScene->setEqualizerVisible(checked);
}

void TestWindow::on_aSplit_triggered(bool checked)
{
    m_amarokScene->setButtonMode(checked ? AmarokScene::SplittedButtons : AmarokScene::VerticalStack);
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

void TestWindow::on_actionCool_Theme_triggered()
{
    m_amarokScene->setTheme(new CoolbarTheme);
}
