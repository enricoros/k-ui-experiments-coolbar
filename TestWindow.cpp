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
#include "AmarokCoolbar.h"
#include "ui_TestWindow.h"
#include <QCoreApplication>

TestWindow::TestWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::TestWindow)
  , m_coolBar(new AmarokCoolbar(QApplication::applicationDirPath()))
{
    // setup GUI
    ui->setupUi(this);
    ui->containerLayout->addWidget(m_coolBar->view());
    foreach (const QString & name, m_coolBar->themeNames())
        ui->themeCombo->addItem(name);
    foreach (const QString & name, m_coolBar->layoutNames())
        ui->layoutCombo->addItem(name);

    // check actions
    AmarokScene * scene = m_coolBar->scene();
    ui->aAnalyzer->setChecked(scene->analyzerVisible());
    ui->aAnimateLayouting->setChecked(scene->layoutAnimationEnabled());
    ui->aAnimateResize->setChecked(scene->resizeAnimationEnabled());
}

TestWindow::~TestWindow()
{
    delete m_coolBar;
    delete ui;
}

void TestWindow::on_aAnalyzer_triggered(bool checked)
{
    m_coolBar->scene()->setAnalyzerVisible(checked);
}

void TestWindow::on_aAnimateLayouting_triggered(bool checked)
{
    m_coolBar->scene()->setLayoutAnimationEnabled(checked);
}

void TestWindow::on_aAnimateResize_triggered(bool checked)
{
    m_coolBar->scene()->setResizeAnimationEnabled(checked);
}

void TestWindow::on_themeCombo_currentIndexChanged(int index)
{
    m_coolBar->setTheme(index);
}

void TestWindow::on_layoutCombo_currentIndexChanged(int index)
{
    m_coolBar->setLayout(index);
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
