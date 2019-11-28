#include "block.h"
#include "board.h"

using namespace std;
vector<Cell&> Block::getCells() {
	return cells;
}
void Block::setCells(const vector<Cell&> newCells) {
	cells.clear();
	cells = newCells;
}
Colour Block::getColour() {
	return colour;
}

Block::Block(Cell& c1, Cell& c2, Cell& c3, Cell& c4,
	int heavy, Colour colour) : heavy{ heavy },
	colour{ colour }, state{ 1 } {
	cells.emplace_back(c1);
	cells.emplace_back(c2);
	cells.emplace_back(c3);
	cells.emplace_back(c4);
}

void Block::moveDownByOne(Board& playerBoard) {
	bool canMove = 1;
	vector<vector<Cell>> board = playerBoard.getBoard();

	for (int i = 0; i < 4; ++i) {
		Coordinates curCoord = cells.at(i).getinfo().coord;
		if (board.at(curCoord.row + 1).at(curCoord.col).getinfo().colour
			!= Colour::White
			&& board.at(curCoord.row + 1).at(curCoord.col).getCurrBlock
			== false) canMove = 0;
	}

	if (canMove) {
		vector<Cell&> newCells;
		
		for (int i = 0; i < 4; ++i) {
			Cell& oldCell = cells.at(i);
			Coordinates currCoord = oldCell.getinfo().coord;
			Cell& newCell = board.at(currCoord.row + 1).at(currCoord.col);
			// Change target cell (one cell down)
			newCell.setColour(oldCell.getinfo().colour);
			newCell.setCurrBlock(true);

			// change current cell
			oldCell.setColour(Colour::White);
			oldCell.setCurrBlock(false);
			// get new cell
			newCells.emplace_back(newCell);
		}
		cells = newCells;
	}
}

void Block::moveDown(Board& playerBoard) {
	moveDownByOne(playerBoard);
	for (int i = 0; i < heavy; ++i) moveDownByOne(playerBoard);
}

void Block::moveLeft(Board& playerBoard) {
	bool canMove = 1;
	vector<vector<Cell>> board = playerBoard.getBoard();

	//check if it can go to left by 1 column.
	for (int i = 0; i < 4; ++i) {
		Coordinates curCoord = cells.at(i).getinfo().coord;
		if (curCoord.col == 0 // if already first col
			|| (board.at(curCoord.row).at(curCoord.col - 1).getinfo().colour
				!= Colour::White && (board.at(curCoord.row).at(curCoord.col - 1).getCurrBlock()
					== false))) canMove = 0;
	}

	if (canMove) {
		vector<Cell&> newCells;
		for (int i = 0; i < 4; ++i) {
			Cell& oldCell = cells.at(i);
			Coordinates currCoord = oldCell.getinfo().coord;
			Cell& newCell = board.at(currCoord.row).at(currCoord.col - 1);
			// Change target cell (one cell down)
			newCell.setColour(oldCell.getinfo().colour);
			newCell.setCurrBlock(true);

			// change current cell
			oldCell.setColour(Colour::White);
			newCell.setCurrBlock(false);
			// get new cell
			newCells.emplace_back(newCell);
		}
		for (int i = 0; i < heavy; ++i) moveDownByOne(playerBoard);
		cells = newCells;
	}
}
void Block::moveRight(Board& playerBoard) {
	bool canMove = 1;
	vector<vector<Cell>> board = playerBoard.getBoard();

	//check if it can go to left by 1 column.
	for (int i = 0; i < 4; ++i) {
		Coordinates curCoord = cells.at(i).getinfo().coord;
		if (curCoord.col == 17 // if already first col
			|| (board.at(curCoord.row).at(curCoord.col + 1).getinfo().colour
				!= Colour::White && (board.at(curCoord.row).at(curCoord.col + 1).getCurrBlock()
					== false))) canMove = 0;
	}

	if (canMove) {
		vector<Cell&> newCells;
		for (int i = 0; i < 4; ++i) {
			Cell& oldCell = cells.at(i);
			Coordinates currCoord = oldCell.getinfo().coord;
			Cell& newCell = board.at(currCoord.row).at(currCoord.col + 1);
			// Change target cell (one cell down)
			newCell.setColour(oldCell.getinfo().colour);
			newCell.setCurrBlock(true);

			// change current cell
			oldCell.setColour(Colour::White);
			newCell.setCurrBlock(false);
			// get new cell
			newCells.emplace_back(newCell);
		}
		for (int i = 0; i < heavy; ++i) moveDownByOne(playerBoard);
		cells = newCells;
	}
}

void Block::drop(Board& playerBoard) {
	for (int i = 0; i < 20; ++i) moveDownByOne(playerBoard);
}
