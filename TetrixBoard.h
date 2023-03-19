#pragma once
#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include <QLabel>
#include "tetrixpiece.h"
#include <QDebug>

class TetrixBoard : public QFrame
{
	Q_OBJECT

public:
	TetrixBoard(QWidget* parent = nullptr);
	void setNextPieceLabel(QLabel* label);

public slots:
	void start();
	void pause();

signals:
	void scoreChanged(int score);
	void levelChanged(int level);
	void linesRemovedChanged(int numLines);

protected:
	void paintEvent(QPaintEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void timerEvent(QTimerEvent* event) override;


private:
	// number of squares per row and column
	enum { BoardWidth = 10, BoardHeight = 30 };

	TetrixShape& shapeAt(int i, int j) { return nowBoard[i][j]; }
	// width and height of a square
	int squareWidth() { return contentsRect().width() / BoardWidth; }
	int squareHeight() { return contentsRect().height() / BoardHeight; }
	void newPiece();
	void clearBoard();

	void pieceDropped();
	void oneLineDown();
	void dropDown();
	void removeFullLines();

	void showNextPiece();
	void drawSquare(QPainter& painter, int x, int y, TetrixShape shape);
	int timeOutTime() {return 1000 / (1 + level); }
	bool tryMove(const TetrixPiece& newPiece, int newX, int newY);

	QBasicTimer timer;
	bool isPaused;
	bool isStarted;
	QPointer<QLabel> nextPieceLabel;
	TetrixPiece curPiece;
	TetrixPiece nextPiece;
	// position of current piece, according to the coordinate direction of Qt (left to right, top to bottom)
	int curX;
	int curY;
	int numLinesRemoved;
	int score;
	int level;
	int numPiecesDropped; // number of pieces dropped since started
	bool isLineRemoved; // whether at least 1 line removed this time
	TetrixShape nowBoard[BoardWidth][BoardHeight];
};


