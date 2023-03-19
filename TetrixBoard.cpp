#include "tetrixboard.h"

#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
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
    isLineRemoved = false;
    numLinesRemoved = 0;
    score = 0;
    level = 1;
    numPiecesDropped = 0;
    clearBoard();


    emit linesRemovedChanged(numLinesRemoved);
    emit scoreChanged(score);
    emit levelChanged(level);

    newPiece();
    timer.start(timeOutTime(), this);
}

// pause the game 
void TetrixBoard::pause()
{
    if (!isStarted)
        return;

    
    if (isPaused) {
        timer.start(timeOutTime(), this);
    }
    else {
        timer.stop();
    }
    isPaused = !isPaused;
    update();
    
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
        //nowBoard[x][y] = curPiece.shape();
        shapeAt(x, y) = curPiece.shape();
    }

    // level up every 50 pieces
    numPiecesDropped++;
    if (numPiecesDropped % 50 == 0 && level < 5) {
		level++;
		timer.start(timeOutTime(), this);
        emit levelChanged(level);
	}
    
    removeFullLines();
    qDebug() << "next 2" << endl;
    if (!isLineRemoved)
        newPiece();

}


//// move lines if it is full
void TetrixBoard::removeFullLines()
{
    int numFullLines = 0;
    for (int i = 1; i < BoardHeight; i++) {
        bool lineIsFull = true;
        for (int j = 0; j < BoardWidth; j++) {
            if (shapeAt(j, i) == NoShape) {
				lineIsFull = false;
				break;
			}
		}

        if (lineIsFull) {
            numFullLines++;
            for (int k = i; k > 1; k--) {
                for (int j = 0; j < BoardWidth; j++) {
					shapeAt(j, k) = shapeAt(j, k - 1);
				}
			}
            
            for (int j = 0; j < BoardWidth; j++) {
                shapeAt(j, 1) = NoShape;
            }
            qDebug() << "removed" << endl;
        }
    }

    if (numFullLines > 0) {
        numLinesRemoved += numFullLines;
        
        switch (numFullLines) {
            case 1:
			    score += 10;
			    break;
            case 2:
                score += 30;
                break;
            case 3:
                score += 60;
				break;
            case 4:
                score += 100;
                break;
            default:
                break;
        }
        emit linesRemovedChanged(numLinesRemoved);
        emit scoreChanged(score);

        timer.start(500, this);
        isLineRemoved = true;
        curPiece.setShape(NoShape);
        update();
    }
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

    if (!tryMove(curPiece, curX, curY)) {
		curPiece.setShape(NoShape);
		timer.stop();
		isStarted = false;
	}
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
    static constexpr QRgb colorTable[8] = {
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

    if (isPaused) {
        painter.setFont(QFont("Courier", 20, QFont::DemiBold));
        painter.drawText(rect, Qt::AlignCenter, tr("Paused"));
    }

    // paint exsisted piece
    int boardTop = rect.bottom() - BoardHeight * squareHeight();
    for (int i = 0; i < BoardWidth; i++) {
        for (int j = BoardHeight - 1; j >= 0; j--) {
            TetrixShape shape = shapeAt(i, j);
            if (shape != NoShape) {
                drawSquare(painter, rect.left() + i * squareWidth(), boardTop + j * squareHeight(), shape);
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
    if (!isStarted || isPaused || curPiece.shape() == NoShape) {
        QFrame::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
        case Qt::Key_Left:
            tryMove(curPiece, curX - 1, curY);
            break;
        case Qt::Key_Right:
            tryMove(curPiece, curX + 1, curY);
		    break;
        case Qt::Key_Z:
			tryMove(curPiece.rotatedLeft(), curX, curY);
			break;
        case Qt::Key_X:
            tryMove(curPiece.rotatedRight(), curX, curY);
            break;
        case Qt::Key_Down:
            oneLineDown();
			break;
        default:
            QFrame::keyPressEvent(event);
    }
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

