#include "tetrixboard.h"

#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
// qdebug
#include <QDebug>

TetrixBoard::TetrixBoard(QWidget* parent)
    : QFrame(parent), isStarted(false), isPaused(false)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    clearBoard();
    nextPiece.setRandomShape();
}

// set the label to show the next piece
void TetrixBoard::setNextPieceLabel(QLabel* label)
{
	nextPieceLabel = label;
}

// clear the board
void TetrixBoard::clearBoard()
{
    for (int i = 0; i < BoardWidth; i++) {
        for (int j = 0; j < BoardHeight; j++) {
            nowBoard[i][j].setShape(NoShape);
        }
    }
}

// start the game
void TetrixBoard::start()
{
    if (isPaused)
	    return;

    isStarted = true;
    isPaused = false;
    numLinesRemoved = 0;
    score = 0;
    level = 1;
    numPiecesDropped = 0;
    clearBoard();

    // 控制台输出111
    qDebug() << "111";

    emit linesRemovedChanged(numLinesRemoved);
    emit scoreChanged(score);
    emit levelChanged(level);

    newPiece();
    timer.start(timeOutTime(), this);
}

void TetrixBoard::pause()
{

}

// generate newPiece
void TetrixBoard::newPiece()
{
    curPiece = nextPiece;
    nextPiece.setRandomShape();
    showNextPiece();

    curX = BoardWidth / 2 + 1;
    curY = 1 - curPiece.minY();

}

// nextPiece place, use label to show
void TetrixBoard::showNextPiece()
{
    if (!nextPieceLabel)
        return;

    int dx = nextPiece.maxX() - nextPiece.minX() + 1;
    int dy = nextPiece.maxY() - nextPiece.minY() + 1;

    QPixmap pixmap(dx * squareWidth(), dy * squareHeight());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), nextPieceLabel->palette().background());
    for (int i = 0; i < 4; i++) {
        int x = nextPiece.x(i) - nextPiece.minX();
        int y = nextPiece.y(i) - nextPiece.minY();
        drawSquare(painter, x * squareWidth(), y * squareHeight(), nextPiece.shape()); 
    }
    nextPieceLabel->setPixmap(pixmap);
}

void TetrixBoard::drawSquare(QPainter& painter, int x, int y, TetrixShape shape)
{
    static const QRgb colorTable[8] = {
		0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
		0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
	};

    QColor color = colorTable[shape];
    painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2, color);
    painter.setPen(color.lighter());
    painter.drawLine(x, y + squareHeight() - 1, x, y);
    painter.drawLine(x + squareWidth() - 1, y, x, y);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1, x, y + squareHeight() - 1);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1, x + squareWidth() - 1, y);
}


void TetrixBoard::paintEvent(QPaintEvent* event)
{
    
    QFrame::paintEvent(event);
    QPainter painter(this);
    QRect rect = contentsRect();

    // paint current piece
    if (curPiece.shape() != NoShape) {
        for (int i = 0; i < 4; i++) {
            
        }
    }
}

bool tryMove(const TetrixPiece& newPiece, int newX, int newY)
{

}