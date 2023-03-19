#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TetrixWindow.h"
#include "TetrixBoard.h"
#include <QMessageBox>

class TetrixWindow : public QMainWindow
{
    Q_OBJECT

public:
    TetrixWindow(QWidget *parent = nullptr);
    ~TetrixWindow();

protected:
    void paintEvent(QPaintEvent* event) override;

public slots:
    //void testButtonClicked();
    void promptButtonClicked();
private:
    Ui::TetrixWindowClass ui;
    TetrixBoard* board;
};
