#include "LBlock.h"
#include "board.h"
using namespace std;

LBlock::LBlock (Cell* c1, Cell* c2, Cell* c3, Cell* c4,
int heavy, Colour colour): Block{c1,c2,c3,c4,heavy,colour} {}

void LBlock::CWRotate(Board & playerBoard) {
    if (state == 1) {
        Info i3 = cells.at(3)->getinfo();
        playerBoard.getBoard().at(i3.coord.row-2).at(i3.coord.col).
        setColour(i3.colour); 
        cells.at(3)->setColour(Colour::White);

        Info i2 = cells.at(2)->getinfo();
        playerBoard.getBoard().at(i2.coord.row-1).at(i2.coord.col-1).
        setColour(i2.colour); 
        cells.at(2)->setColour(Colour::White);

        Info i1 = cells.at(1)->getinfo();
        playerBoard.getBoard().at(i1.coord.row).at(i1.coord.col-2).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

        Info i0 = cells.at(0)->getinfo();
		playerBoard.getBoard().at(i0.coord.row+1).at(i0.coord.col-1).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            playerBoard.getBoard().at(i0.coord.row-2).at(i0.coord.col));
        newCells.emplace_back(
            playerBoard.getBoard().at(i1.coord.row-1).at(i1.coord.col-1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i2.coord.row).at(i2.coord.col-2));
        newCells.emplace_back(
            playerBoard.getBoard().at(i3.coord.row+1).at(i3.coord.col-1));
        
        cells.clear();
        cells = newCells;
        state = 2;
    } else if (state == 2) {
        Info i0 = cells.at(0)->getinfo();
        // check if rotation is legit
        if (i0.coord.col == 17) return;

        // if rotation is legit.
        Info i3 = cells.at(3)->getinfo();
        playerBoard.getBoard().at(i3.coord.row+1).at(i3.coord.col+2).
        setColour(i3.colour); 
        cells.at(3)->setColour(Colour::White);

        Info i2 = cells.at(2)->getinfo();
        playerBoard.getBoard().at(i2.coord.row).at(i2.coord.col+1).
        setColour(i2.colour); 
        cells.at(2)->setColour(Colour::White);

        Info i1 = cells.at(1)->getinfo();
        playerBoard.getBoard().at(i1.coord.row-1).at(i1.coord.col).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

		playerBoard.getBoard().at(i0.coord.row).at(i0.coord.col-1).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            playerBoard.getBoard().at(i0.coord.row).at(i0.coord.col-1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i1.coord.row-1).at(i1.coord.col));
        newCells.emplace_back(
            playerBoard.getBoard().at(i2.coord.row).at(i2.coord.col+1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i3.coord.row+1).at(i3.coord.col+2));
        
        cells.clear();
        cells = newCells;
        state = 3;
    } else if (state == 3) {
        Info i3 = cells.at(3)->getinfo();
        playerBoard.getBoard().at(i3.coord.row+1).at(i3.coord.col-1).
        setColour(i3.colour); 
        cells.at(3)->setColour(Colour::White);

        // do not need to change cell 2
        Info i2 = cells.at(2)->getinfo();

        Info i1 = cells.at(1)->getinfo();
        playerBoard.getBoard().at(i1.coord.row-1).at(i1.coord.col+1).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

        Info i0 = cells.at(0)->getinfo();
		playerBoard.getBoard().at(i0.coord.row-2).at(i0.coord.col).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            playerBoard.getBoard().at(i0.coord.row-2).at(i0.coord.col));
        newCells.emplace_back( // up until here.
            playerBoard.getBoard().at(i1.coord.row-1).at(i1.coord.col+1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i2.coord.row).at(i2.coord.col));
        newCells.emplace_back(
            playerBoard.getBoard().at(i3.coord.row+1).at(i3.coord.col-1));
        
        cells.clear();
        cells = newCells;
        state = 4; 
    } else if (state == 4) {
        Info i0 = cells.at(0)->getinfo();
        // check if rotation is legit
        if (i0.coord.col == 16) return;

        playerBoard.getBoard().at(i0.coord.row+1).at(i0.coord.col+2).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        Info i1 = cells.at(1)->getinfo();
        playerBoard.getBoard().at(i1.coord.row+2).at(i1.coord.col+1).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

        // do nothing for cell 2.
        Info i2 = cells.at(2)->getinfo();
        playerBoard.getBoard().at(i2.coord.row+1).at(i2.coord.col).
        setColour(i3.colour);
        cells.at(2)->setColour(Colour::White);

        Info i3 = cells.at(3)->getinfo();
        playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col-1).
        setColour(i3.colour);
        cells.at(3)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            playerBoard.getBoard().at(i0.coord.row+1).at(i0.coord.col+2));
        newCells.emplace_back( // up until here.
            playerBoard.getBoard().at(i1.coord.row+2).at(i1.coord.col+1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i2.coord.row+1).at(i2.coord.col));
        newCells.emplace_back(
            playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col-1));
        
        cells.clear();
        cells = newCells;
        state = 1; 
    }
    // apply heavy affects.
    for (int i = 0; i < heavy; ++i) moveDownByOne(playerBoard);
}

void LBlock::CounterCWRotate(Board &playerBoard) {
    if (state == 1) {
        Info i0 = cells.at(0)->getinfo();
		playerBoard.getBoard().at(i0.coord.row-1).at(i0.coord.col-1).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        Info i1 = cells.at(1)->getinfo();
        playerBoard.getBoard().at(i1.coord.row-2).at(i1.coord.col-1).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);
        
        Info i2 = cells.at(2)->getinfo();
        playerBoard.getBoard().at(i2.coord.row-1).at(i2.coord.col).
        setColour(i2.colour); 
        cells.at(2)->setColour(Colour::White);

        Info i3 = cells.at(3)->getinfo();
        playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col+1).
        setColour(i3.colour); 
        cells.at(3)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            playerBoard.getBoard().at(i0.coord.row-1).at(i0.coord.col-1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i1.coord.row-2).at(i1.coord.col-1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i2.coord.row-1).at(i2.coord.col));
        newCells.emplace_back(
            playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col+1));
        
        cells.clear();
        cells = newCells;
        state = 4;
    } else if (state == 2) {
        Info i0 = cells.at(0)->getinfo();
        // check if rotation is legit
        if (i0.coord.col == 17) return;

        // if rotation is legit.
        playerBoard.getBoard().at(i0.coord.row-1).at(i0.coord.col+1).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        Info i1 = cells.at(1)->getinfo();
        playerBoard.getBoard().at(i1.coord.row).at(i1.coord.col+2).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

        Info i2 = cells.at(2)->getinfo();
        playerBoard.getBoard().at(i2.coord.row+1).at(i2.coord.col+1).
        setColour(i2.colour); 
        cells.at(2)->setColour(Colour::White);

        Info i3 = cells.at(3)->getinfo();
        playerBoard.getBoard().at(i3.coord.row+2).at(i3.coord.col).
        setColour(i3.colour);
        cells.at(3)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            playerBoard.getBoard().at(i0.coord.row-1).at(i0.coord.col+1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i1.coord.row).at(i1.coord.col+2));
        newCells.emplace_back(
            playerBoard.getBoard().at(i2.coord.row+1).at(i2.coord.col+1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i3.coord.row+2).at(i3.coord.col));
        
        cells.clear();
        cells = newCells;
        state = 1;
    } else if (state == 3) {
        Info i0 = cells.at(0)->getinfo();
        playerBoard.getBoard().at(i0.coord.row).at(i0.coord.col+1).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        Info i1 = cells.at(1)->getinfo();
        playerBoard.getBoard().at(i1.coord.row+1).at(i1.coord.col).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

        Info i3 = cells.at(3)->getinfo();
        playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col-1).
        setColour(i3.colour);
        cells.at(3)->setColour(Colour::White);

        Info i2 = cells.at(2)->getinfo();
        playerBoard.getBoard().at(i2.coord.row-1).at(i2.coord.col-2).
        setColour(i2.colour);
        cells.at(2)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            playerBoard.getBoard().at(i0.coord.row).at(i0.coord.col+1));
        newCells.emplace_back( // up until here.
            playerBoard.getBoard().at(i1.coord.row+1).at(i1.coord.col));
        newCells.emplace_back(
            playerBoard.getBoard().at(i2.coord.row).at(i2.coord.col-1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i3.coord.row-1).at(i3.coord.col-2));
        
        cells.clear();
        cells = newCells;
        state = 2; 
    } else if (state == 4) { 
        Info i0 = cells.at(0)->getinfo();
        // check if rotation is legit
        if (i0.coord.col == 16) return;

        playerBoard.getBoard().at(i0.coord.row+2).at(i0.coord.col).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        Info i1 = cells.at(1)->getinfo();
        playerBoard.getBoard().at(i1.coord.row+1).at(i1.coord.col-1).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

        // do nothing for cell 2.
        Info i2 = cells.at(2)->getinfo();

        Info i3 = cells.at(3)->getinfo();
        playerBoard.getBoard().at(i3.coord.row-1).at(i3.coord.col+1).
        setColour(i3.colour);
        cells.at(3)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            playerBoard.getBoard().at(i0.coord.row+2).at(i0.coord.col));
        newCells.emplace_back( // up until here.
            playerBoard.getBoard().at(i1.coord.row+1).at(i1.coord.col-1));
        newCells.emplace_back(
            playerBoard.getBoard().at(i2.coord.row).at(i2.coord.col));
        newCells.emplace_back(
            playerBoard.getBoard().at(i3.coord.row-1).at(i3.coord.col+1));
        
        cells.clear();
        cells = newCells;
        state = 3; 
    }
    // apply heavy affects.
    for (int i = 0; i < heavy; ++i) moveDownByOne(playerBoard);
}
