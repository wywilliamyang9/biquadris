#ifndef _LEVEL_
#define _LEVEL_
#include "colour.h"
#include <string>
#include "subject.h"
#include "blockInfo.h"
class Block;
class Level{
    int level;
    int heavy = 0;

    int seed;
    int blocknum;

    protected:
    Colour nextBlock;
    Colour currBlock;

    public:
    Level(int seed, int blocknum);
    void forceBlock(Colour type); // when special action "Force" is applied
    void addHeavy(); // when special action "Heavy" is applied
    int getLevel(); // returns current level
    Block* createBlock(Colour type);
    virtual BlockInfo generateNextBlock() = 0; // spawn next block
    Colour getNextBlock();
    virtual void setSequence(std::string filename) = 0;
    virtual int calculateScore(int rowsCleared) = 0; // calculates got score
};
#endif
