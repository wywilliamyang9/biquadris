#ifndef _LEVEL_
#define _LEVEL_
#include "block.h"
#include "colour.h"
#include "subject.h"

class Level{
    int level;
    int heavy = 0;
    Colour nextBlock;
    Block* currBlock;
    int seed;

    public:
    void forceBlock(Colour type); // when special action "Force" is applied
    void addHeavy(); // when special action "Heavy" is applied
    int getLevel(); // returns current level
    Block* createBlock(Colour type);
    virtual Block* generateNextBlock() = 0; // spawn next block
    Colour getNextBlock();
    virtual int calculateScore(int rowSCleared) = 0; // calculates got score
};
#endif
