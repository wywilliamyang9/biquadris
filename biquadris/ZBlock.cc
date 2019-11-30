#include "ZBlock.h"
#include "board.h"
using namespace std;

ZBlock::ZBlock (Cell* c1, Cell* c2, Cell* c3, Cell* c4,
int heavy, Colour colour): Block{c1,c2,c3,c4,heavy,colour} {}

void ZBlock::CWRotate(Board & playerBoard) {
    if (state == 1) {
        Info i0 = cells.at(0)->getinfo();
		playerBoard.getBoard().at(i0.coord.row-1).at(i0.coord.col+1).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        Info i1 = cells.at(1)->getinfo();

        Info i2 = cells.at(2)->getinfo();
        playerBoard.getBoard().at(i2.coord.row-1).at(i2.coord.col-1).
        setColour(i2.colour); 
        cells.at(2)->setColour(Colour::White);

        Info i3 = cells.at(3)->getinfo();
        playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col-2).
        setColour(i3.colour); 
        cells.at(3)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            playerBoard.getBoard().at(i0.coord.row-1).at(i0.coord.col+1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i1.coord.row).at(i1.coord.col));
        newCells.emplace_back(
            playerBoard.getBoard().at(i2.coord.row-1).at(i2.coord.col-1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col-2));
        for (int i = 0; i < 4; ++i) {
            cells.at(i).setCurrBlock(false);
            newCells.at(i).setCurrBlock(true);
        }
        cells.clear();
        cells = newCells;
        state = 2;
    } else if (state == 2) {
        Info i0 = cells.at(0)->getinfo();
        // check if rotation is legit
        if (i0.coord.col == 17) return;

        // if rotation is legit.
        Info i3 = cells.at(3)->getinfo();
        playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col+2).
        setColour(i3.colour); 
        cells.at(3)->setColour(Colour::White);
        
        Info i2 = cells.at(2)->getinfo();
        playerBoard.getBoard().at(i2.coord.row+1).at(i2.coord.col+1).
        setColour(i2.colour); 
        cells.at(2)->setColour(Colour::White);

        Info i1 = cells.at(1)->getinfo();

		playerBoard.getBoard().at(i0.coord.row+1).at(i0.coord.col-1).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            playerBoard.getBoard().at(i0.coord.row+1).at(i0.coord.col-1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i1.coord.row).at(i1.coord.col));
        newCells.emplace_back(
            playerBoard.getBoard().at(i2.coord.row+1).at(i2.coord.col+1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col+2));
        for (int i = 0; i < 4; ++i) {
            cells.at(i).setCurrBlock(false);
            newCells.at(i).setCurrBlock(true);
        }
        cells.clear();
        cells = newCells;
        state = 1;
    } 
    // apply heavy affects.
    for (int i = 0; i < heavy; ++i) moveDownByOne(playerBoard);
}

void SBlock::CounterCWRotate(Board &playerBoard) {
    CWRotate(playerBoard);
}
