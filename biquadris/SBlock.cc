#include "SBlock.h"
#include "board.h"
using namespace std;

SBlock::SBlock (Cell* c1, Cell* c2, Cell* c3, Cell* c4,
int heavy, Colour colour,int spawnLevel): Block{c1,c2,c3,c4,heavy,colour,spawnLevel} {}

void SBlock::CWRotate(Board & playerBoard) {
    if (state == 1) {
        Info i0 = cells.at(0)->getinfo();
        Info i1 = cells.at(1)->getinfo();
        Info i2 = cells.at(2)->getinfo();
        Info i3 = cells.at(3)->getinfo();

        bool canRotate = 1;
        if (playerBoard.getBoard().at(i1.coord.row-1).at(i1.coord.col-1).
        getColour() != Colour::White) canRotate = 0;
        if (playerBoard.getBoard().at(i0.coord.row-2).at(i0.coord.col).
        getColour() != Colour::White) canRotate = 0;
        if (!canRotate) return;

		playerBoard.getBoard().at(i0.coord.row-2).at(i0.coord.col).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        playerBoard.getBoard().at(i1.coord.row-1).at(i1.coord.col-1).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

        playerBoard.getBoard().at(i3.coord.row+1).at(i3.coord.col-1).
        setColour(i3.colour); 
        cells.at(3)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i0.coord.row-2).at(i0.coord.col)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i1.coord.row-1).at(i1.coord.col-1)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i2.coord.row).at(i2.coord.col)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i3.coord.row+1).at(i3.coord.col-1)));
        for (int i = 0; i < 4; ++i) {
            cells.at(i)->setCurrBlock(false);
        }    
        for (int i = 0; i < 4; ++i) {
            newCells.at(i)->setCurrBlock(true);
        }  
        cells.clear();
        cells = newCells;
        state = 2;
    } else if (state == 2) {
        Info i0 = cells.at(0)->getinfo();
        Info i3 = cells.at(3)->getinfo();
        Info i2 = cells.at(2)->getinfo();
        Info i1 = cells.at(1)->getinfo();

        // check if rotation is legit
        if (i0.coord.col == 9) return;

        bool canRotate = 1;
        if (playerBoard.getBoard().at(i3.coord.row-1).at(i3.coord.col+1).
        getColour() != Colour::White) canRotate = 0;
        if (playerBoard.getBoard().at(i0.coord.row+2).at(i0.coord.col).
        getColour() != Colour::White) canRotate = 0;
        if (!canRotate) return;

        // if rotation is legit.
        playerBoard.getBoard().at(i3.coord.row-1).at(i3.coord.col+1).
        setColour(i3.colour); 
        cells.at(3)->setColour(Colour::White);

        playerBoard.getBoard().at(i1.coord.row+1).at(i1.coord.col+1).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

		playerBoard.getBoard().at(i0.coord.row+2).at(i0.coord.col).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i0.coord.row+2).at(i0.coord.col)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i1.coord.row+1).at(i1.coord.col+1)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i2.coord.row).at(i2.coord.col)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i3.coord.row-1).at(i3.coord.col+1)));
        for (int i = 0; i < 4; ++i) {
            cells.at(i)->setCurrBlock(false);
        }    
        for (int i = 0; i < 4; ++i) {
            newCells.at(i)->setCurrBlock(true);
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
