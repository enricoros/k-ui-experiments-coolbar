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

#ifndef __TestWindow_h__
#define __TestWindow_h__

#include <QMainWindow>
namespace Ui { class TestWindow; }
class AmarokCoolarScene;
class CoolarView;


class TestWindow : public QMainWindow
{
    Q_OBJECT
    public:
        TestWindow(QWidget *parent = 0);
        ~TestWindow();

    private:
        Ui::TestWindow *ui;
        CoolarView * m_view;
        AmarokCoolarScene * m_acs;

    private slots:
        void on_aSplit_triggered(bool checked);
        void on_aEq_triggered(bool checked);
        void on_actionDesktop_Size_triggered();
        void on_actionNetbook_Size_triggered();
        void on_actionIStuff_Size_triggered();
};

#endif
