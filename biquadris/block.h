#ifndef _BLOCK_
#define _BLOCK_
#include <vector>
#include "colour.h"
#include "coordinates.h"
#include "cell.h"
//#include "board.h"

class Board;
class Block {
    std::vector<Cell*> cells;
    int heavy;
    Colour colour;
    int state;
    public:
    Block (Cell*, Cell*, Cell*, Cell*,
         int heavy, Colour);

    std::vector<Cell*> getCells();
    void setCells(const std::vector<Cell&>);
    Colour getColour();

    void moveDown(Board& playerBoard);
    void moveLeft(Board&);
    void moveRight(Board &);
	void moveDownByOne(Board&);
    void drop(Board &);
    virtual void CWRotate(Board &) = 0;
    virtual void CounterCWRotate(Board &) = 0;
};
#endif
