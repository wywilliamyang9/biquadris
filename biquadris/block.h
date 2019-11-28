#ifndef _BLOCK_
#define _BLOCK_
#include <vector>
#include "colour.h"
#include "coordinates.h"
class Block {
    vector<Cell&> cells;
    int heavy;
    Colour colour;
    int state;
    public:
    Block (Cell&, Cell&, Cell&, Cell&,
         int heavy, Colour);

    vector<Cell&> getCells();
    void setCells(const vector<Cell>&);
    Colour getcolour();

    void moveDown(Board &);
    void moveLeft(Board &);
    void moveRight(Board &);
    void drop(Board &);
    virtual void CWRotate(Board &) = 0;
    virtual void CounterCWRotate(Board &) = 0;
};
#endif
