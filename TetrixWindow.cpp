#include "TetrixWindow.h"
#include "TetrixBoard.h"
#include <QPainter>
TetrixWindow::TetrixWindow(QWidget *parent)
    : QMainWindow(parent), board(new TetrixBoard)
{
    ui.setupUi(this);
    
    ui.boardFrame->setLayout(new QHBoxLayout);
    ui.boardFrame->layout()->addWidget(board);

    board->setNextPieceLabel(ui.nextPieceLabel);
    // button function
    connect(ui.startButton, &QPushButton::clicked, board, &TetrixBoard::start);
    connect(ui.pauseButton, &QPushButton::clicked, board, &TetrixBoard::pause);
    connect(ui.promptButton, &QPushButton::clicked, this, &TetrixWindow::promptButtonClicked);
    // LCD changed function
    //connect(board, &TetrixBoard::scoreChanged, ui.scoreNumber, &QLCDNumber::display);
    connect(board, &TetrixBoard::scoreChanged, ui.scoreNumber, QOverload<int>::of(&QLCDNumber::display));
    connect(board, &TetrixBoard::levelChanged, ui.levelNumber, QOverload<int>::of(&QLCDNumber::display));
    connect(board, &TetrixBoard::linesRemovedChanged, ui.lineNumber, QOverload<int>::of(&QLCDNumber::display));

}

TetrixWindow::~TetrixWindow()
{}

void TetrixWindow::promptButtonClicked()
{
    QMessageBox msgBox;

    msgBox.setText("     How to play the game:    ");
    msgBox.setInformativeText("  ← →: move left and right;\n   ↓：move faster;\n   z: rotate left;\n   x: rotate right;\n    ");

    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void TetrixWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    //painter.drawPixmap(rect(), QPixmap("./images/tae.jpg"), QRect());
    //painter.drawPixmap(rect(), QPixmap("./images/yelan.jpg"), QRect());
    painter.drawPixmap(rect(), QPixmap("./images/makoto.jpg"), QRect());


}