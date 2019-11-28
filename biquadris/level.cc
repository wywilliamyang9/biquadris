#include "level.h"
#include "block.h"
#include "cell.h"
#include "colour.h"

using namespace std;

Level::Level(int seed, int blocknum): seed{seed}, blocknum{blocknum){}

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

Block* Level::createBlock(){
    if (convertColour(nextBlock) == 'I'){
        Block *block = new Block{make_share<Cell>(3, 0, blocknum), make_share<Cell>(3, 1, blocknum), make_share<Cell>(3, 2, blocknum), make_share<Cell>(3, 3, blocknum), heavy, nextBlock};
        heavy = 0;
        return block;
    } else if (convertColour(nextBlock) == 'J'){
        Block *block = new Block{make_share<Cell>(2, 0, blocknum), make_share<Cell>(3, 0, blocknum), make_share<Cell>(3, 1, blocknum), make_share<Cell>(3, 2, blocknum), heavy, nextBlock};
        heavy = 0;
        return block;
    } else if (convertColour(nextBlock) == 'L'){
        Block *block = new Block{make_share<Cell>(2, 2, blocknum), make_share<Cell>(3, 2, blocknum), make_share<Cell>(3, 1, blocknum), make_share<Cell>(3, 0, blocknum), heavy, nextBlock};
        heavy = 0;
        return block;
    } else if (convertColour(nextBlock) == 'O'){
        Block *block = new Block{make_share<Cell>(2, 0, blocknum), make_share<Cell>(2, 1, blocknum), make_share<Cell>(3, 0, blocknum), make_share<Cell>(3, 1, blocknum), heavy, nextBlock};
        heavy = 0;
        return block;
    } else if (convertColour(nextBlock) == 'S'){
        Block *block = new Block{make_share<Cell>(3, 0, blocknum), make_share<Cell>(3, 1, blocknum), make_share<Cell>(2, 1, blocknum), make_share<Cell>(2, 2, blocknum), heavy, nextBlock};
        heavy = 0;
        return block;
    } else if (convertColour(nextBlock) == 'J'){
        Block *block = new Block{make_share<Cell>(2, 0, blocknum), make_share<Cell>(2, 1, blocknum), make_share<Cell>(3, 1, blocknum), make_share<Cell>(3, 2, blocknum), heavy, nextBlock};
        heavy = 0;
        return block;
    } else if (convertColour(nextBlock) == 'J'){
        Block *block = new Block{make_share<Cell>(2, 0, blocknum), make_share<Cell>(2, 1, blocknum), make_share<Cell>(2, 2, blocknum), make_share<Cell>(3, 1, blocknum), heavy, nextBlock};
        heavy = 0;
        return block;
    }
}
