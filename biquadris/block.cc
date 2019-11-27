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
    for (int i = 0; i < 4; ++i) {
        Coordinates curCoord = cells.at(i).getInfo().coordinates;
        //check if it can go 1 row down.
        if board.at(curCoord.row+1).at(curCoord.col).getInfo().colour
        != Colour::White) canMove = 0;
    }

    if (canMove) {
        vector<Cells> newCells;
        for (int i = 0; i < 4; ++i) {
            // Change target cell (one cell down)
            Info currInfo = cells.at(i).getinfo();
            Coordinates currCoord= currInfo.coordinates;
            board.at(currCoord.row+1).at(currCoord.col).setInfo(
            board.at(currCoord.row+1).at(currCoord.col).getinfo().coordinates,
            currInfo.colour, // only changes colour
            board.at(currCoord.row+1).at(currCoord.col).getinfo().blinded);

            // change current cell
            cells.at(i).setInfo(cells.at(i).getinfo().coordinates,
            Colour::White, cells.at(i).getinfo().blinded);
            newCells.emplace_back
        }
    }
}
void moveLeft();
void moveRight();
void drop();

};




