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

#ifndef __Window_h__
#define __Window_h__

#include <QMainWindow>
namespace Ui { class Window; }
class AmarokCoolbar;


class Window : public QMainWindow
{
    Q_OBJECT
    public:
        Window(QWidget *parent = 0);
        ~Window();

    private:
        Ui::Window * ui;
        AmarokCoolbar * m_coolBar;

    private Q_SLOTS:
        void on_aAnalyzer_triggered(bool checked);
        void on_aAnimateLayouting_triggered(bool checked);
        void on_aAnimateResize_triggered(bool checked);

        void on_themeCombo_currentIndexChanged(int index);
        void on_layoutCombo_currentIndexChanged(int index);

        void on_actionDesktop_Size_triggered();
        void on_actionNetbook_Size_triggered();
        void on_actionIStuff_Size_triggered();
};

#endif
