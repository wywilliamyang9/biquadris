#ifndef _LEVEL0_
#define _LEVEL0_
#include "blockinfo.h"
#include  "level.h"
#include <string>

clase Level0 : public Level{
    std::string scriptFile;
    std::fstream sequence;
    public:
    Level0(int seed, int blocknum, std::string scriptFile);
    BlockInfo generateNextBlock() override;
    void setSequence(std::string filename) override;
    int calculateScore(int rowsCleared) override;
}


#endif
