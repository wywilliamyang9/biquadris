#ifndef _LEVEL_
#define _LEVEL_
#include "block.h"
#include "colour.h"
#include "subject.h"

class Level{
    int level;
    int heavy;
    Colour nextBlock;
    Block* currBlock;
    int seed;

    public:

    void forceBlock(char); // when special action "Force" is applied
    void addHeavy(); // when special action "Heavy" is applied
    int getLevel(); // returns current level
    virtual Block* generateNextBlock() = 0; // spawn next block
    Colour getNextBlock();
    int calculateScore(int rowSCleared); // calculates got score
};
#endif
