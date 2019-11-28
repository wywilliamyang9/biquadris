#ifndef _LEVEL_
#define _LEVEL_
#include "block.h"
#include "colour.h"
#include <string>
#include "subject.h"

class Level{
    int level;
    int heavy = 0;
    Colour nextBlock;
    Block* currBlock;
    int seed;
    int blocknum;

    public:
    Level(int seed, int blocknum);
    void forceBlock(Colour type); // when special action "Force" is applied
    void addHeavy(); // when special action "Heavy" is applied
    int getLevel(); // returns current level
    Block* createBlock(Colour type);
    virtual Block* generateNextBlock() = 0; // spawn next block
    Colour getNextBlock();
    virtual void setSequence(std::string filename) = 0;
    virtual int calculateScore(int rowsCleared) = 0; // calculates got score
};
#endif
