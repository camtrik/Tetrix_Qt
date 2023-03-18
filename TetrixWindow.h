#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TetrixWindow.h"
#include "TetrixBoard.h"


class TetrixWindow : public QMainWindow
{
    Q_OBJECT

public:
    TetrixWindow(QWidget *parent = nullptr);
    ~TetrixWindow();

private slots:
    //void testButtonClicked();

private:
    Ui::TetrixWindowClass ui;
    TetrixBoard* board;
};
