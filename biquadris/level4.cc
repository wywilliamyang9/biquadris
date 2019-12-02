#include "level4.h"
#include <fstream>
#include "colour.h"
#include "blockInfo.h"
#include <string>

using namespace std;


Level4::Level4(int seed, int level,bool readFromFile, std::string scriptFile) :
	Level{ seed, level }, readFromFile{ readFromFile }, dotCount {0}{
#ifdef DEBUG
cout << "Level4 construction starts" << endl;
#endif
	if (readFromFile) {
		this->scriptFile = scriptFile;
		sequence.open(scriptFile);
		string type;
		sequence >> type;
		nextBlock = convertString(type);
	}
}

Colour Level4::chooseNext() {
	int num = rand() % 9;
	if (num == 0 || num == 1) {
		return convertString("S");
	} else if (num == 2 || num == 3) {
		return convertString("Z");
	} else if (num == 4) {
		return convertString("I");
	} else if (num == 5) {
		return convertString("J");
	} else if (num == 6) {
		return convertString("L");
	} else if (num == 7) {
		return convertString("O");
	} else {
		return convertString("T");
	}
}

BlockInfo Level4::generateNextBlock() {
	currBlock = nextBlock;
	if (readFromFile) {
		string type;
		if (!(sequence >> type)) {
			sequence.clear();
			//sequence.seekg(0, sequence.beg);
			sequence.close();
			sequence.open(scriptFile);
			sequence >> type;
		}
		nextBlock = convertString(type);
	}
	else {
		nextBlock = chooseNext();
	}
	heavy++;
	bool spawnDot = false;
	if (!(dotCount % 5)) {
		spawnDot = true;
	}
	dotCountAddOne();
	return BlockInfo{ heavy, currBlock, spawnDot};
}

void Level4::setSequence(std::string filename) {
	if (sequence.is_open()) sequence.close();
	readFromFile = true;
	scriptFile = filename;
	sequence.open(filename);
	string type;
	sequence >> type;
	nextBlock = convertString(type);
}

int Level4::calculateScore(int rowsCleared) {
	int linesClearScore = rowsCleared + level;
	linesClearScore = linesClearScore * linesClearScore;
	return linesClearScore;
}

void Level4::setRandom() {
	readFromFile = false;
}

void Level4::dotCountAddOne() {dotCount++;}

Level4::~Level4(){
	if (sequence.is_open()) sequence.close();
}
