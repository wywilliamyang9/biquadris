#ifndef _BLOCK_
#define _BLOCK_
#include <vector>
#include "colour.h"
#include "coordinates.h"
class Block {
    vector<Cell> cells;
    char type;
    int heavy;
    Colour colour;

    public:
    Block (Cell&, Cell&, Cell&, Cell&,
        char type, int heavy, Colour);

    void moveDown(Board &);
    void moveLeft(Board &);
    void moveRight(Board &);
    void drop(Board &);
    virtual void CWRotate(Board &) = 0;
    virtual void CounterCWRotate(Board &) = 0;
};
#endif
