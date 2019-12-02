#ifndef _OBSERVER_
#define _OBSERVER_
#include "nextBlock.h"
#include <vector>

class Subject;
class Observer {
    public:
    virtual void notify(Subject &caller) = 0;
    virtual ~Observer() = default;
    virtual void updateNextBlock(NextBlock nextBlockInfo) = 0;
    virtual void updateScore(std::vector<int> scores) = 0;
    virtual void updateScore(int newScore, int boardnum) = 0;
    virtual void updateLevel(std::vector<int> levels) = 0;
    virtual void updateLevel(int newLevel, int boardnum) = 0;
};

#endif
