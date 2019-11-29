#ifndef _LEVEL_
#define _LEVEL_
#include "colour.h"
#include <string>
#include "subject.h"
#include "blockInfo.h"
class Block;
class Level{
    protected:

	int level;
	int heavy = 0;

	int seed;

    Colour nextBlock;
    Colour currBlock;

    public:
    Level(int seed);
    void forceBlock(Colour type); // when special action "Force" is applied
    void addHeavy(); // when special action "Heavy" is applied
	void clearHeavy(); // sets heavy to 0
    int getLevel(); // returns current level
    Block* createBlock(Colour type);
    virtual BlockInfo generateNextBlock() = 0; // spawn next block
    Colour getNextBlock();
    virtual void setSequence(std::string filename) = 0;
    virtual int calculateScore(int rowsCleared) = 0; // calculates got score

    void setRandom() = 0;
};
#endif
