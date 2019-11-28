#include "level0.h"
#include "block.h"
#include <fstream>
#include "colour.h"
#include <string>

using namespace std;


Level0::Level0(int seed, int blocknum, std::string scriptFile): 
Level{seed, blocknum}, scriptFile{scriptFile}{
    sequence.open(scriptFile);
    string type;
    sequence >> type;
    nextBlock = convertString(type);
}

Block* Level0::generateNextBlock(){
    currBlock = nextBlock;
    string type;
    if (!(sequence >> type)){
        sequence.clear();
        sequence.seekg(0, sequence.beg);
        sequence >> type;
    }
    nextBlock = convertString(type);
    return currBlock;
}

void Level0::setSequence(std::string filename){
    sequence = filename;
}

int Level0::calculateScore(int rowsCleared){
    int linesClearScore = rowsCleared + level;
    linesClearScore = linesClearScore * linesClearScore;
    return linesClearScore;
}

