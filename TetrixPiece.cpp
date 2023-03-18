#include "TetrixPiece.h"
#include <ctime>
#include <cstdlib>

void TetrixPiece::setShape(TetrixShape shape)
{
	// relative coordinates of the 4 blocks
	static const int coordsTable[8][4][2] = {
		{ { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
		{ { 0, -1 }, { 0, 0 }, { -1, 0 }, { -1, 1 } },
		{ { 0, -1 }, { 0, 0 }, { 1, 0 }, { 1, 1 } },
		{ { 0, -1 }, { 0, 0 }, { 0, 1 }, { 0, 2 } },
		{ { -1, 0 }, { 0, 0 }, { 1, 0 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } },
		{ { -1, -1 }, { 0, -1 }, { 0, 0 }, { 0, 1 } },
		{ { 1, -1 }, { 0, -1 }, { 0, 0 }, { 0, 1 } }
	};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			coords[i][j] = coordsTable[shape][i][j];
		}
	}
	pieceShape = shape;
}

void TetrixPiece::setRandomShape()
{
	srand(time(NULL));
	int x = rand() % 7 + 1;
	TetrixShape shape = TetrixShape(x);
	setShape(shape);
	//setShape(TetrixShape(QRandomGenerator::global()->bounded(7) + 1));
}

// rotate Left: x = y, y = -x
TetrixPiece TetrixPiece::rotateLeft() const
{
	if (pieceShape == SquareShape)
		return *this;
	TetrixPiece result;
	for (int i = 0; i < 4; i++) {
		result.setX(i, y(i));
		result.setY(i, -x(i));
	}
	return result;
}

// rotate Right: x = -y, y = x
TetrixPiece TetrixPiece::rotateRight() const
{
	if (pieceShape == SquareShape)
		return *this;
	TetrixPiece result;
	for (int i = 0; i < 4; i++) {
		result.setX(i, -y(i));
		result.setY(i, x(i));
	}
	return result;
}

int TetrixPiece::minX() const
{
	int min = coords[0][0];
	for (int i = 1; i < 4; i++) {
		if (coords[i][0] < min)
			min = coords[i][0];
	}
	return min;
}

int TetrixPiece::maxX() const
{
	int max = coords[0][0];
	for (int i = 1; i < 4; i++) {
		if (coords[i][0] > max)
			max = coords[i][0];
	}
	return max;
}

int TetrixPiece::minY() const
{
	int min = coords[0][1];
	for (int i = 1; i < 4; i++) {
		if (coords[i][1] < min)
			min = coords[i][1];
	}
	return min;
}

int TetrixPiece::maxY() const
{
	int max = coords[0][1];
	for (int i = 1; i < 4; i++) {
		if (coords[i][1] > max)
			max = coords[i][1];
	}
	return max;
}