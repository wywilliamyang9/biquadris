#include "IBlock.h"
IBlock::IBlock (Cell& c1, Cell& c2, Cell& c3, Cell& c4,
int heavy, Colour colour): heavy {heavy},
colour {colour}, state{1};

Block::Block(Cell& c1, Cell& c2, Cell& c3, Cell& c4,
int heavy, Colour colour): heavy {heavy},
colour {colour}, state{1}; {
    cells.emplace_back(c1);
    cells.emplace_back(c2);
    cells.emplace_back(c3);
    cells.emplace_back(c4);
}


    void CWRotate(Board &)override;
    void CounterCWRotate(Board &)override;