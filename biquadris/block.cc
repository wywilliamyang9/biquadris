#include "block.cc"

vector<Cell>& Block::getCells() {
    return cells;
}
void Block::setCells(const vector<Cell>& newCells){
    cells.clear();
    cells = newCells;
}
Colour Block::getColour() {
    return colour;
}

Block::Block(Cell& c1, Cell& c2, Cell& c3, Cell& c4,
int heavy, Colour colour): heavy {heavy},
colour {colour}, state{1}; {
    cells.emplace_back(c1);
    cells.emplace_back(c2);
    cells.emplace_back(c3);
    cells.emplace_back(c4);
}

void Block::moveDownByOne(Board & playerBoard) {
    bool canMove = 1;
    vector<vector<char>>& board = playerBoard.getBoard();

    for (int i = 0; i < 4; ++i) {
        Coordinates curCoord = cells.at(i).getInfo().coordinates;
        if (board.at(curCoord.row+1).at(curCoord.col).getInfo().colour
        != Colour::White
        && board.at(curCoord.row+1).at(curCoord.col).getCurrBlock
        == false) canMove = 0;
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
                newCell.getinfo().blinded
                newCell.getinfo().boardnum);
            newCell.setCurrBlock(true);

            // change current cell
            oldCell.setInfo(
                oldCell.getinfo().coordinates,
                Colour::White,
                oldCell.getinfo().blinded,
                newCell.getinfo().boardnum);
            oldCell.setCurrBlock(false);
            // get new cell
            newCells.emplace_back(newCell);
        }
        cells = newCells;
    }
}

void Block::moveDown(Board & playerBoard) {
    moveDownByOne();
    for (int i = 0; i < heavy; ++i) moveDownByOne(playerBoard);
}

void Block::moveLeft(Board & playerBoard){
    bool canMove = 1;
    vector<vector<char>>& board = playerBoard.getBoard();

    //check if it can go to left by 1 column.
    for (int i = 0; i < 4; ++i) {
        Coordinates curCoord = cells.at(i).getInfo().coordinates;
        if (curCoord.col == 0 // if already first col
        || (board.at(curCoord.row).at(curCoord.col-1).getInfo().colour
        != Colour::White && (board.at(curCoord.row).at(curCoord.col-1).getCurrBlock()
        == false))) canMove = 0;
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
                newCell.getinfo().blinded
                newCell.getinfo().boardnum);
            newCell.setCurrBlock(true);

            // change current cell
            oldCell.setInfo(
                oldCell.getinfo().coordinates,
                Colour::White,
                oldCell.getinfo().blinded
                oldCell.getinfo().boardnum);
            newCell.setCurrBlock(false);
            // get new cell
            newCells.emplace_back(newCell);
        }
        for (int i = 0; i < heavy; ++i) moveDownByOne(playerBoard);
        cells = newCells;
    }
}
void Block::moveRight(Board & playerBoard){
    bool canMove = 1;
    vector<vector<char>>& board = playerBoard.getBoard();

    //check if it can go to left by 1 column.
    for (int i = 0; i < 4; ++i) {
        Coordinates curCoord = cells.at(i).getInfo().coordinates;
        if (curCoord.col == 17 // if already first col
        || (board.at(curCoord.row).at(curCoord.col+1).getInfo().colour
        != Colour::White && (board.at(curCoord.row).at(curCoord.col+1).getCurrBlock()
        == false))) canMove = 0;
    }

    if (canMove) {
        vector<Cells> newCells;
        for (int i = 0; i < 4; ++i) {
            Cell& oldCell = cells.at(i);
            Cell& newCell = board.at(currCoord.row).at(currCoord.col+1);
            // Change target cell (one cell down)
            newCell.setInfo(
                newCell.getinfo().coordinates,
                oldCell.getinfo().colour, // only changes colour
                newCell.getinfo().blinded
                newCell.getinfo().boardnum);
            newCell.setCurrBlock(true);

            // change current cell
            oldCell.setInfo(
                oldCell.getinfo().coordinates,
                Colour::White,
                oldCell.getinfo().blinded
                oldCell.getinfo().boardnum);
            newCell.setCurrBlock(false);
            // get new cell
            newCells.emplace_back(newCell);
        }
        for (int i = 0; i < heavy; ++i) moveDownByOne(playerBoard);
        cells = newCells;
    }
}

void drop(){
    for (int i = 0; i < 20; ++i) moveDownByOne();
}
