#include "level1.h"
#include "block.h"
#include <fstream>
#include "colour.h"
#include "blockinfo.h"
#include <string>

using namespace std;


Level1::Level1(int seed, int blocknum, bool readFromFile,std::string scriptFile = ""): 
Level{seed, blocknum}, readFromFile{readFromFile}{
    if (readFromFile){
        this->scriptFile = scriptFile;
        sequence.open(scriptFile);
        string type;
        sequence >> type;
        nextBlock = convertString(type);
    }
}

Colour Level1::chooseNext(){
    int num = rand()%12;
    if (num == 0){

    } else 
}

BlockInfo Level1::generateNextBlock(){
    currBlock = nextBlock;
    string type;
    if (!(sequence >> type)){
        sequence.clear();
        sequence.seekg(0, sequence.beg);
        sequence >> type;
    }
    nextBlock = convertString(type);
    return BlockInfo{currBlock, heavy};
}

void Level1::setSequence(std::string filename){
    sequence = filename;
}

int Level1::calculateScore(int rowsCleared){
    int linesClearScore = rowsCleared + level;
    linesClearScore = linesClearScore * linesClearScore;
    return linesClearScore;
}

