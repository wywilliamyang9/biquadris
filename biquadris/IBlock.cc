#include "IBlock.h"
IBlock::IBlock (Cell& c1, Cell& c2, Cell& c3, Cell& c4,
int heavy, Colour colour): Block{c1,c2,c3,c4,heavy,colour} {}

void IBlock::CWRotate(Board & playerBoard) {
    vector<vector<Cells>>& board = playerBoard.getBoard();
    if (state == 1) {
        Info i0 = cells.at(0).getinfo();
        board.at(i0.coordinates.row-3,i0.coordinates.col).setInfo(
            Coordinate {i0.coordinates.row-3,i0.coordinates.col}
            i0.colour;
            i0.blinded;
            i0.boardnum;
        );
        cells.at(0).setInfo(
            i0.coordinates;
            Colour::White;
            i0.blinded;
            i0.boardnum;
        );

        Info i1 = cells.at(1).getinfo();
        board.at(i1.coordinates.row-2,i1.coordinates.col-1).setInfo(
            Coordinate {i1.coordinates.row-2,i1.coordinates.col-1};
            i1.colour;
            i1.blinded;
            i1.boardnum;
        ); 
        cells.at(1).setInfo(
            i1.coordinates;
            Colour::White;
            i1.blinded;
            i1.boardnum;
        );
     
        Info i2 = cells.at(2).getinfo();
        board.at(i2.coordinates.row-1,i2.coordinates.col-2).setInfo(
            Coordinate {i2.coordinates.row-1,i2.coordinates.col-2};
            i2.colour;
            i2.blinded;
            i2.boardnum;
        ); 
        cells.at(2).setInfo(
            i2.coordinates;
            Colour::White;
            i2.blinded;
            i2.boardnum;
        );

        Info i3 = cells.at(3).getinfo();
        board.at(i3.coordinates.row,i3.coordinates.col-3).setInfo(
            Coordinate {i3.coordinates.row,i3.coordinates.col-3};
            i3.colour;
            i3.blinded;
            i3.boardnum;
        ); 
        cells.at(3).setInfo(
            i3.coordinates;
            Colour::White;
            i3.blinded;
            i3.boardnum;
        );
        
        vector<Cells&> newCells;
        newCells.emplace_back(
            board.at(i0.coordinates.row-3,i0.coordinates.col)); 
        newCells.emplace_back(
            board.at(i1.coordinates.row-2,i1.coordinates.col-1)); 
        newCells.emplace_back(
            board.at(i2.coordinates.row-1,i2.coordinates.col-2));
        newCells.emplace_back(
            board.at(i3.coordinates.row,i3.coordinates.col-3));
        
        cells.clear();
        cells = newCells;
        state = 2;
    } else if (state == 2) {
        Info i0 = cells.at(0).getinfo();
        // check if rotation is legit
        if (i0.coordinates(col)+3 > 17) return;

        // if rotation is legit.
        Info i3 = cells.at(3).getinfo();
        board.at(i3.coordinates.row,i3.coordinates.col+3).setInfo(
            Coordinate {i3.coordinates.row,i3.coordinates.col+3};
            i3.colour;
            i3.blinded;
            i3.boardnum;
        ); 
        cells.at(3).setInfo(
            i3.coordinates;
            Colour::White;
            i3.blinded;
            i3.boardnum;
        );

        Info i2 = cells.at(2).getinfo();
        board.at(i2.coordinates.row+1,i2.coordinates.col+2).setInfo(
            Coordinate {i2.coordinates.row+1,i2.coordinates.col+2};
            i2.colour;
            i2.blinded;
            i2.boardnum;
        ); 
        cells.at(2).setInfo(
            i2.coordinates;
            Colour::White;
            i2.blinded;
            i2.boardnum;
        );

        Info i1 = cells.at(1).getinfo();
        board.at(i1.coordinates.row+2,i1.coordinates.col+1).setInfo(
            Coordinate {i1.coordinates.row+2,i1.coordinates.col+1};
            i1.colour;
            i1.blinded;
            i1.boardnum;
        ); 
        cells.at(1).setInfo(
            i1.coordinates;
            Colour::White;
            i1.blinded;
            i1.boardnum;
        );
        board.at(i0.coordinates.row+3,i0.coordinates.col).setInfo(
            Coordinate {i0.coordinates.row+3,i0.coordinates.col}
            i0.colour;
            i0.blinded;
            i0.boardnum;
        );
        cells.at(0).setInfo(
            i0.coordinates;
            Colour::White;
            i0.blinded;
            i0.boardnum;
        );

        vector<Cells&> newCells;
        newCells.emplace_back(
            board.at(i0.coordinates.row+3,i0.coordinates.col)); 
        newCells.emplace_back(
            board.at(i1.coordinates.row+2,i1.coordinates.col+1)); 
        newCells.emplace_back(
            board.at(i2.coordinates.row+1,i2.coordinates.col+2));
        newCells.emplace_back(
            board.at(i3.coordinates.row,i3.coordinates.col+3));
        
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
