#ifndef _LEVEL1_
#define _LEVEL1_
#include "blockInfo.h"
#include  "level.h"
#include <string>

clase Level1 : public Level{
    std::string scriptFile;
    bool readFromFile;
    std::fstream sequence;
    public:
    Level1(int seed, int blocknum, std::string scriptFile);
    Colour chooseNext();
    BlockInfo generateNextBlock() override;
    void setSequence(std::string filename) override;
    int calculateScore(int rowsCleared) override;
}


#endif
