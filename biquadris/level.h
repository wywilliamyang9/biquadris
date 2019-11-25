#ifndef _LEVEL_
#define _LEVEL_
#include "block.h"
#include "subject.h"

class Level : Subject <char> {
    Observer observers;

    int level;
    int heavy;
    char nextBlock;

    public:
    char getinfo() const override;

    void forceBlock(char); // when special action "Force" is applied
    void addHeavy(); // when special action "Heavy" is applied
    int getLevel(); // returns current level
    virtual Block generateNextBlock() = 0; // spawn next block
    int calculateScore(int rowSCleared); // calculates got score
};
#endif
