#ifndef _BLOCK_
#define _BLOCK_
#include <vector>
#include <Colour>

class Block {
    vector<vector<Cell>> cells;
    char type;
    int heavy;
    Colour colour;

    public:
    void moveDown(int);
    void moveLeft(int);
    void moveRight(int);
    void drop();
    virtual void CWRotate(int) = 0;
    virtual void CounterCWRotate(int) = 0;
};
#endif
