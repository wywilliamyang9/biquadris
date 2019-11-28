#include "IBlock.h"
IBlock::IBlock (Cell* c1, Cell* c2, Cell* c3, Cell* c4,
int heavy, Colour colour): Block{c1,c2,c3,c4,heavy,colour} {}

void IBlock::CWRotate(Board & playerBoard) {
    vector<vector<Cells>>& board = playerBoard.getBoard();
    if (state == 1) {
        Info i0 = cells.at(0)->getinfo();
        playerBoard.getBoard().at(i0.coordinates.row-3,i0.coordinates.col).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        Info i1 = cells.at(1)->getinfo();
        playerBoard.getBoard().at(i1.coordinates.row-2,i1.coordinates.col-1).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);
     
        Info i2 = cells.at(2)->getinfo();
        playerBoard.getBoard().at(i2.coordinates.row-1,i2.coordinates.col-2).
        setColour(i2.colour); 
        cells.at(2)->setColour(Colour::White);

        Info i3 = cells.at(3)->getinfo();
        playerBoard.getBoard().at(i3.coordinates.row,i3.coordinates.col-3).
        setColour(i3.colour); 
        cells.at(3)->setColour(Colour::White);
        
        vector<Cells*> newCells;
        newCells.emplace_back(
            playerBoard.getBoard().at(i0.coordinates.row-3,i0.coordinates.col)); 
        newCells.emplace_back(
            playerBoard.getBoard().at(i1.coordinates.row-2,i1.coordinates.col-1)); 
        newCells.emplace_back(
            playerBoard.getBoard().at(i2.coordinates.row-1,i2.coordinates.col-2));
        newCells.emplace_back(
            playerBoard.getBoard().at(i3.coordinates.row,i3.coordinates.col-3));
        
        cells.clear();
        cells = newCells;
        state = 2;
    } else if (state == 2) {
        Info i0 = cells.at(0).getinfo();
        // check if rotation is legit
        if (i0.coordinates(col)+3 > 17) return;

        // if rotation is legit.
        Info i3 = cells.at(3)->getinfo();
        playerBoard.getBoard().at(i3.coordinates.row,i3.coordinates.col+3).
        setColour(i3.colour);
        cells.at(3)->setColour(Colour::White);

        Info i2 = cells.at(2)->getinfo();
        playerBoard.getBoard().at(i2.coordinates.row+1,i2.coordinates.col+2).
        setColour(i2.colour); 
        cells.at(2)->setColour(Colour::White);

        Info i1 = cells.at(1)->getinfo();
        playerBoard.getBoard().at(i1.coordinates.row+2,i1.coordinates.col+1).
        setColour(i1.colour); 
        cells.at(1)->setColour(Colour::White);

        Info i0 = cells.at(1)->getinfo();
        playerBoard.getBoard().at(i0.coordinates.row+3,i0.coordinates.col).
        setColour(i0.colour);
        cells.at(0)->setColour(Colour::White);

        vector<Cells&> newCells;
        newCells.emplace_back(
            playerBoard.getBoard().at(i0.coordinates.row+3,i0.coordinates.col)); 
        newCells.emplace_back(
            playerBoard.getBoard().at(i1.coordinates.row+2,i1.coordinates.col+1)); 
        newCells.emplace_back(
            playerBoard.getBoard().at(i2.coordinates.row+1,i2.coordinates.col+2));
        newCells.emplace_back(
            playerBoard.getBoard().at(i3.coordinates.row,i3.coordinates.col+3));
        
        cells.clear();
        cells = newCells;
        state = 1;
    }
    // apply heavy affects.
    for (int i = 0; i < heavy; ++i) moveDownByOne(playerBoard);
}

void IBlock::CounterCWRotate(Board &playerBoard) {
    CWRotate(playerBoard);
}
