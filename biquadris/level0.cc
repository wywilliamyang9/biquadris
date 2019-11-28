#include "level0.h"
#include "block.h"
#include <fstream>

using namespace std;


Level0::Level0(int seed, int blocknum, std::string scriptFile): 
Level{seed, blocknum}, scriptFile{scriptFile}{
    sequence.open(scriptFile);
}

Block* Level0::generateNextBlock(){

}

void Level0::setSequence(std::string filename){

}

int Level0::calculateScore(int rowsCleared){

}

