#include "level0.h"
#include "block.h"
#include <fstream>
#include "colour.h"
#include "blockInfo.h"
#include <string>

using namespace std;


Level0::Level0(int seed, std::string scriptFile): 
Level{seed}, scriptFile{scriptFile}{
    sequence.open(scriptFile);
    string type;
    sequence >> type;
    nextBlock = convertString(type);
}

BlockInfo Level0::generateNextBlock(){
    currBlock = nextBlock;
    string type;
    if (!(sequence >> type)){
        sequence.clear();
        sequence.seekg(0, sequence.beg);
        sequence >> type;
    }
    nextBlock = convertString(type);
    return BlockInfo{heavy,currBlock };
}

void Level0::setSequence(std::string filename){
    scriptFile = filename;
    sequence.open(filename);
    string type;
    sequence >> type;
    nextBlock = convertString(type);
}

int Level0::calculateScore(int rowsCleared){
    int linesClearScore = rowsCleared + level;
    linesClearScore = linesClearScore * linesClearScore;
    return linesClearScore;
}
