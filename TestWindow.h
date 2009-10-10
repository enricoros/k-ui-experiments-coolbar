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

#ifndef __TestWindow_h__
#define __TestWindow_h__

#include <QMainWindow>
namespace Ui { class TestWindow; }
class AmarokScene;
class CoolbarView;


class TestWindow : public QMainWindow
{
    Q_OBJECT
    public:
        TestWindow(QWidget *parent = 0);
        ~TestWindow();

    private:
        Ui::TestWindow *ui;
        CoolbarView * m_view;
        AmarokScene * m_amarokScene;

    private slots:
        void on_actionCool_Theme_triggered();
        void on_aSplit_triggered(bool checked);
        void on_aEq_triggered(bool checked);
        void on_actionDesktop_Size_triggered();
        void on_actionNetbook_Size_triggered();
        void on_actionIStuff_Size_triggered();
};

#endif
