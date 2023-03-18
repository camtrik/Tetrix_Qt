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
            nowBoard[i][j] = NoShape;
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

// pause the game 
void TetrixBoard::pause()
{

}

void TetrixBoard::oneLineDown()
{
    if (!tryMove(curPiece, curX, curY + 1))
		pieceDropped();
}

// Dropped pieces, change the shape at the position of the piece
void TetrixBoard::pieceDropped()
{
    for (int i = 0; i < 4; i++) {
        int x = curPiece.x(i) + curX;
        int y = curPiece.y(i) + curY;
        nowBoard[x][y] = curPiece.shape();
        //shapeAt(x, y) = curPiece.shape();
    }

    // level up every 50 pieces
    numPiecesDropped++;
    if (numPiecesDropped % 50 == 0 && level < 5) {
		level++;
		timer.start(timeOutTime(), this);
        emit levelChanged(level);
	}
    
    removeFullLines();
    if (!isLineRemoved)
        newPiece();

}

// move lines if it is full
void TetrixBoard::removeFullLines()
{

}

// generate newPiece
void TetrixBoard::newPiece()
{
    curPiece = nextPiece;
    nextPiece.setRandomShape();
    showNextPiece();

    // initialize curX and curY, which is the center coor of the piece
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

// draw one square
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

// paint event, was called by Qt every time the board is changed
void TetrixBoard::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);
    QRect rect = contentsRect();

    // paint exsisted piece
    int boardTop = rect.bottom() - BoardHeight * squareHeight();
    if (curPiece.shape() != NoShape) {
        for (int i = 0; i < BoardWidth; i++) {
            for (int j = 0; j < BoardHeight; j++) {
                TetrixShape shape = shapeAt(i, j);
                if (shape != NoShape) {
                    drawSquare(painter, rect.left() + i * squareWidth(), boardTop + j * squareHeight(), shape);
                }
            }
        }
    }

    // paint current piece
    if (curPiece.shape() != NoShape) {
        for (int i = 0; i < 4; i++) {
            int x = curX + curPiece.x(i);
            int y = curY + curPiece.y(i);
            drawSquare(painter, rect.left() + x * squareWidth(), boardTop + y * squareHeight(), curPiece.shape());
        }
   }
}

// timer event, was called by Qt every time the timer is timeout
void TetrixBoard::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == timer.timerId()) {
        if (isLineRemoved) {
            isLineRemoved = false;
            newPiece();
            timer.start(timeOutTime(), this);
        }
        else {
			oneLineDown();
        }
    }
    else
		QFrame::timerEvent(event);

}

void TetrixBoard::keyPressEvent(QKeyEvent* event)
{

}

// decide whether the piece can move, if can move, move it
bool TetrixBoard::tryMove(const TetrixPiece& newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; i++) {
        int x = newX + newPiece.x(i);
        int y = newY + newPiece.y(i);
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
			return false;
        if (shapeAt(x, y) != NoShape)
            return false;
    }
    curPiece = newPiece;
    curX = newX;
    curY = newY;
    update();
    return true;
}