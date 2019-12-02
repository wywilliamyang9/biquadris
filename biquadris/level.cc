#include "level.h"
#include "cell.h"
#include "colour.h"

using namespace std;

Level::Level(int seed, int level) : level{level}, seed{ seed },
nextBlock {Colour::White},currBlock {Colour::White}{
	srand(seed);
}
void Level::clearHeavy() {
	heavy = 0;
}
void Level::forceBlock(Colour forcedBlock) {
	nextBlock = forcedBlock;
}

void Level::addHeavy() {
	heavy++;
}

int Level::getLevel() {
	return level;
}

Colour Level::getNextBlock() {
	return nextBlock;
}
