#include "TetrixWindow.h"
#include "TetrixBoard.h"

TetrixWindow::TetrixWindow(QWidget *parent)
    : QMainWindow(parent), board(new TetrixBoard)
{
    ui.setupUi(this);
    
    // 将board放到boardFrame中，水平布局
    ui.boardFrame->setLayout(new QHBoxLayout);
    ui.boardFrame->layout()->addWidget(board);

    board->setNextPieceLabel(ui.nextPieceLabel);
    connect(ui.startButton, &QPushButton::clicked, board, &TetrixBoard::start);

    //connect(ui.startButton, &QPushButton::clicked, board, &TetrixBoard::start);
  
    //connect(ui.testButton, &QPushButton::clicked, this, &TetrixWindow::testButtonClicked);
}

TetrixWindow::~TetrixWindow()
{}

//void TetrixWindow::testButtonClicked()
//{
//	ui.testLabel->setText("Clicked");
//}
