#include "TBlock.h"
#include "board.h"
#include "cell.h"

using namespace std;

TBlock::TBlock (Cell* c1, Cell* c2, Cell* c3, Cell* c4,
int heavy, Colour colour,int spawnLevel): Block{c1,c2,c3,c4,heavy,colour,spawnLevel} {}

void TBlock::CWRotate(Board & playerBoard) {
    if (state == 1) {
        Info i0 = cells.at(0)->getinfo();
        Info i1 = cells.at(1)->getinfo();
        Info i2 = cells.at(2)->getinfo();
        Info i3 = cells.at(3)->getinfo();

        bool canRotate = 1;
        if (playerBoard.getBoard().at(i0.coord.row-1).at(i0.coord.col+1).
        getColour() != Colour::White) canRotate = 0;
        if (!canRotate) return;

		playerBoard.getBoard().at(i0.coord.row-1).at(i0.coord.col+1).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);       

        playerBoard.getBoard().at(i3.coord.row-1).at(i3.coord.col-1).
        setColour(i3.colour); 
        cells.at(3)->setColour(Colour::White);

        playerBoard.getBoard().at(i2.coord.row+1).at(i2.coord.col-1).
        setColour(i2.colour); 
        cells.at(2)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i0.coord.row-1).at(i0.coord.col+1)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i1.coord.row).at(i1.coord.col)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i2.coord.row+1).at(i2.coord.col-1)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i3.coord.row-1).at(i3.coord.col-1)));
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
        Info i2 = cells.at(2)->getinfo();
        Info i1 = cells.at(1)->getinfo();
        Info i3 = cells.at(3)->getinfo();

        // check if rotation is legit
        if (i0.coord.col == 10) return;

        bool canRotate = 1;
        if (playerBoard.getBoard().at(i2.coord.row).at(i2.coord.col-1).
        getColour() != Colour::White) canRotate = 0;
        if (playerBoard.getBoard().at(i0.coord.row+2).at(i0.coord.col+1).
        getColour() != Colour::White) canRotate = 0;
        if (!canRotate) return;

		playerBoard.getBoard().at(i0.coord.row+2).at(i0.coord.col+1).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        playerBoard.getBoard().at(i2.coord.row).at(i2.coord.col-1).
        setColour(i2.colour); 
        cells.at(2)->setColour(Colour::White);

        playerBoard.getBoard().at(i1.coord.row+1).at(i1.coord.col).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

        // if rotation is legit.
        playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col+1).
        setColour(i3.colour); 
        cells.at(3)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i0.coord.row+2).at(i0.coord.col+1)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i1.coord.row+1).at(i1.coord.col)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i2.coord.row).at(i2.coord.col-1)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col+1)));
        for (int i = 0; i < 4; ++i) {
            cells.at(i)->setCurrBlock(false);
        }    
        for (int i = 0; i < 4; ++i) {
            newCells.at(i)->setCurrBlock(true);
        }  
        cells.clear();
        cells = newCells;
        state = 3;
    } else if (state == 3) {
        Info i3 = cells.at(3)->getinfo();
        Info i2 = cells.at(2)->getinfo();
        Info i1 = cells.at(1)->getinfo();
        Info i0 = cells.at(0)->getinfo();

        bool canRotate = 1;
        if (playerBoard.getBoard().at(i1.coord.row-1).at(i1.coord.col-1).
        getColour() != Colour::White) canRotate = 0;
        if (playerBoard.getBoard().at(i2.coord.row-2).at(i2.coord.col).
        getColour() != Colour::White) canRotate = 0;
        if (!canRotate) return;

        // do not need to change cell 2
        playerBoard.getBoard().at(i2.coord.row-2).at(i2.coord.col).
        setColour(i2.colour); 
        cells.at(2)->setColour(Colour::White);

        playerBoard.getBoard().at(i1.coord.row-1).at(i1.coord.col-1).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

		playerBoard.getBoard().at(i0.coord.row).at(i0.coord.col-2).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i0.coord.row).at(i0.coord.col-2)));
        newCells.emplace_back( // up until here.
            &(playerBoard.getBoard().at(i1.coord.row-1).at(i1.coord.col-1)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i2.coord.row-2).at(i2.coord.col)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col)));
        for (int i = 0; i < 4; ++i) {
            cells.at(i)->setCurrBlock(false);
        }    
        for (int i = 0; i < 4; ++i) {
            newCells.at(i)->setCurrBlock(true);
        }  
        cells.clear();
        cells = newCells;
        state = 4; 
    } else if (state == 4) {
        Info i0 = cells.at(0)->getinfo();
        Info i1 = cells.at(1)->getinfo();
        Info i2 = cells.at(2)->getinfo();
        Info i3 = cells.at(3)->getinfo();

        // check if rotation is legit
        if (i0.coord.col == 9) return;

        bool canRotate = 1;
        if (playerBoard.getBoard().at(i3.coord.row+1).at(i3.coord.col).
        getColour() != Colour::White) canRotate = 0;
        if (playerBoard.getBoard().at(i2.coord.row+1).at(i2.coord.col+2).
        getColour() != Colour::White) canRotate = 0;
        if (!canRotate) return;

        playerBoard.getBoard().at(i3.coord.row+1).at(i3.coord.col).
        setColour(i3.colour);
        cells.at(3)->setColour(Colour::White);

        playerBoard.getBoard().at(i2.coord.row+1).at(i2.coord.col+2).
        setColour(i2.colour);
        cells.at(2)->setColour(Colour::White);

        playerBoard.getBoard().at(i1.coord.row).at(i1.coord.col+1).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

        playerBoard.getBoard().at(i0.coord.row-1).at(i0.coord.col).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i0.coord.row-1).at(i0.coord.col)));
        newCells.emplace_back( // up until here.
            &(playerBoard.getBoard().at(i1.coord.row).at(i1.coord.col+1)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i2.coord.row+1).at(i2.coord.col+2)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i3.coord.row+1).at(i3.coord.col)));
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

void TBlock::CounterCWRotate(Board &playerBoard) {
    if (state == 1) {
        Info i0 = cells.at(0)->getinfo();
        Info i1 = cells.at(1)->getinfo();
        Info i2 = cells.at(2)->getinfo();
        Info i3 = cells.at(3)->getinfo();

        bool canRotate = 1;
        if (playerBoard.getBoard().at(i0.coord.row+1).at(i0.coord.col).
        getColour() != Colour::White) canRotate = 0;
        if (playerBoard.getBoard().at(i2.coord.row-1).at(i2.coord.col-2).
        getColour() != Colour::White) canRotate = 0;
        if (!canRotate) return;

		playerBoard.getBoard().at(i0.coord.row+1).at(i0.coord.col).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        playerBoard.getBoard().at(i1.coord.row).at(i1.coord.col-1).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);
        
        playerBoard.getBoard().at(i2.coord.row-1).at(i2.coord.col-2).
        setColour(i2.colour); 
        cells.at(2)->setColour(Colour::White);

        playerBoard.getBoard().at(i3.coord.row-1).at(i3.coord.col).
        setColour(i3.colour); 
        cells.at(3)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i0.coord.row+1).at(i0.coord.col)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i1.coord.row).at(i1.coord.col-1)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i2.coord.row-1).at(i2.coord.col-2)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i3.coord.row-1).at(i3.coord.col)));
        for (int i = 0; i < 4; ++i) {
            cells.at(i)->setCurrBlock(false);
        }    
        for (int i = 0; i < 4; ++i) {
            newCells.at(i)->setCurrBlock(true);
        }  
        cells.clear();
        cells = newCells;
        state = 4;
    } else if (state == 2) {
        Info i0 = cells.at(0)->getinfo();
        // check if rotation is legit
        if (i0.coord.col == 10) return;

        // if rotation is legit.
        Info i1 = cells.at(1)->getinfo();
        Info i3 = cells.at(3)->getinfo();
        Info i2 = cells.at(2)->getinfo();

        bool canRotate = 1;
        if (playerBoard.getBoard().at(i2.coord.row-1).at(i2.coord.col+1).
        getColour() != Colour::White) canRotate = 0;
        if (!canRotate) return;


        playerBoard.getBoard().at(i2.coord.row-1).at(i2.coord.col+1).
        setColour(i2.colour); 
        cells.at(2)->setColour(Colour::White);

        playerBoard.getBoard().at(i3.coord.row+1).at(i3.coord.col+1).
        setColour(i3.colour);
        cells.at(3)->setColour(Colour::White);
        
        playerBoard.getBoard().at(i0.coord.row+1).at(i0.coord.col-1).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i0.coord.row+1).at(i0.coord.col-1)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i1.coord.row).at(i1.coord.col)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i2.coord.row-1).at(i2.coord.col+1)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i3.coord.row+1).at(i3.coord.col+1)));
        for (int i = 0; i < 4; ++i) {
            cells.at(i)->setCurrBlock(false);
        }    
        for (int i = 0; i < 4; ++i) {
            newCells.at(i)->setCurrBlock(true);
        }  
        cells.clear();
        cells = newCells;
        state = 1;
    } else if (state == 3) {
        Info i0 = cells.at(0)->getinfo();
        Info i3 = cells.at(3)->getinfo();
        Info i1 = cells.at(1)->getinfo();
        Info i2 = cells.at(2)->getinfo();

        bool canRotate = 1;
        if (playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col-1).
        getColour() != Colour::White) canRotate = 0;
        if (playerBoard.getBoard().at(i0.coord.row-2).at(i0.coord.col-1).
        getColour() != Colour::White) canRotate = 0;
        if (!canRotate) return;

        playerBoard.getBoard().at(i0.coord.row-2).at(i0.coord.col-1).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col-1).
        setColour(i3.colour);
        cells.at(3)->setColour(Colour::White);

        playerBoard.getBoard().at(i1.coord.row-1).at(i1.coord.col).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

        playerBoard.getBoard().at(i2.coord.row).at(i2.coord.col+1).
        setColour(i2.colour);
        cells.at(2)->setColour(Colour::White);

        vector<Cell*> newCells;
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i0.coord.row-2).at(i0.coord.col-1)));
        newCells.emplace_back( // up until here.
            &(playerBoard.getBoard().at(i1.coord.row-1).at(i1.coord.col)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i2.coord.row).at(i2.coord.col+1)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col-1)));
        for (int i = 0; i < 4; ++i) {
            cells.at(i)->setCurrBlock(false);
        }    
        for (int i = 0; i < 4; ++i) {
            newCells.at(i)->setCurrBlock(true);
        }  
        cells.clear();
        cells = newCells;
        state = 2; 
    } else if (state == 4) { 
        Info i0 = cells.at(0)->getinfo();
        Info i1 = cells.at(1)->getinfo();
        Info i2 = cells.at(2)->getinfo();
        Info i3 = cells.at(3)->getinfo();

        // check if rotation is legit
        if (i0.coord.col == 9) return;

        bool canRotate = 1;
        if (playerBoard.getBoard().at(i0.coord.row).at(i0.coord.col+2).
        getColour() != Colour::White) canRotate = 0;
        if (playerBoard.getBoard().at(i1.coord.row+1).at(i1.coord.col+1).
        getColour() != Colour::White) canRotate = 0;
        if (!canRotate) return;

        playerBoard.getBoard().at(i0.coord.row).at(i0.coord.col+2).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        playerBoard.getBoard().at(i1.coord.row+1).at(i1.coord.col+1).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

        playerBoard.getBoard().at(i2.coord.row+2).at(i2.coord.col).
        setColour(i2.colour);
        cells.at(2)->setColour(Colour::White);

        // do nothing for cell 2.

        vector<Cell*> newCells;
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i0.coord.row).at(i0.coord.col+2)));
        newCells.emplace_back( // up until here.
            &(playerBoard.getBoard().at(i1.coord.row+1).at(i1.coord.col+1)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i2.coord.row+2).at(i2.coord.col)));
        newCells.emplace_back(
            &(playerBoard.getBoard().at(i3.coord.row).at(i3.coord.col)));
        for (int i = 0; i < 4; ++i) {
            cells.at(i)->setCurrBlock(false);
        }    
        for (int i = 0; i < 4; ++i) {
            newCells.at(i)->setCurrBlock(true);
        }  
        cells.clear();
        cells = newCells;
        state = 3; 
    }
    // apply heavy affects.
    for (int i = 0; i < heavy; ++i) moveDownByOne(playerBoard);
}
