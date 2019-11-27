#include "block.cc"

Block::Block(Cell& c1, Cell& c2, Cell& c3, Cell& c4,
char type, int heavy, Colour colour): type {type}, heavy {heavy},
colour {colour}  {
    cells.emplace_back(c1);
    cells.emplace_back(c2);
    cells.emplace_back(c3);
    cells.emplace_back(c4);
}

void Block::moveDown(Board & playerBoard) {
    bool canMove = 1;
    vector<vector<char>>& board = playerBoard.getBoard();

    //check if it can go 1 row down.
    for (int i = 0; i < 4; ++i) {
        Coordinates curCoord = cells.at(i).getInfo().coordinates;
        if board.at(curCoord.row+1).at(curCoord.col).getInfo().colour
        != Colour::White) canMove = 0;
    }

    if (canMove) {
        vector<Cells> newCells;
        for (int i = 0; i < 4; ++i) {
            Cell& oldCell = cells.at(i);
            Cell& newCell = board.at(currCoord.row+1).at(currCoord.col);
            // Change target cell (one cell down)
            newCell.setInfo(
                newCell.getinfo().coordinates,
                oldCell.getinfo().colour, // only changes colour
                newCell.getinfo().blinded);

            // change current cell
            oldCell.setInfo(oldCell.getinfo().coordinates,
            Colour::White, oldCell.getinfo().blinded);

            // get new cell
            newCells.emplace_back(newCell);
        }
        cells = newCells;
    }
}

void moveLeft(){
    bool canMove = 1;
    vector<vector<char>>& board = playerBoard.getBoard();

    //check if it can go to left by 1 column.
    for (int i = 0; i < 4; ++i) {
        Coordinates curCoord = cells.at(i).getInfo().coordinates;
        if (curCoord.col == 0 // if already first col
        || board.at(curCoord.row).at(curCoord.col-1).getInfo().colour
        != Colour::White) canMove = 0;
    }

    if (canMove) {
        vector<Cells> newCells;
        for (int i = 0; i < 4; ++i) {
            Cell& oldCell = cells.at(i);
            Cell& newCell = board.at(currCoord.row).at(currCoord.col-1);
            // Change target cell (one cell down)
            newCell.setInfo(
                newCell.getinfo().coordinates,
                oldCell.getinfo().colour, // only changes colour
                newCell.getinfo().blinded);

            // change current cell
            oldCell.setInfo(oldCell.getinfo().coordinates,
            Colour::White, oldCell.getinfo().blinded);

            // get new cell
            newCells.emplace_back(newCell);
        }
        cells = newCells;
    }
}
void moveRight();
void drop();

};




