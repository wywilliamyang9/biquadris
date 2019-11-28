#ifndef _LEVEL0_
#define _LEVEL0_
#include  "level.h"
#include <string>
#include <fstream>

clase Level0 : public Level{
    std::string scriptFile;
    std::fstream sequence;
    public:
    Level0(int seed, int blocknum, std::string scriptFile);
    Block* generateNextBlock() override;
    void setSequence(std::string filename) override;
    int calculateScore(int rowsCleared) override;
}


#endif
