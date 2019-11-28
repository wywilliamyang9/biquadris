#include "level.h"
#include "block.h"
#include "cell.h"
#include "colour.h"

using namespace std;

Level::Level(int seed, int blocknum): seed{seed}, blocknum{blocknum){
    srand(seed);
}

void Level::forceBlock(Colour forcedBlock){
    nextBlock = forceBlock;
}

void Level::addHeavy(){
    heavy++;
}

int Level::getLevel(){
    return level;
}

Colour Level::getNextBlock(){
    return nextBlock;
}

