#include "level2.h"
#include <fstream>
#include "colour.h"
#include "blockInfo.h"
#include <string>

using namespace std;


Level2::Level2(int seed, bool readFromFile, std::string scriptFile) :
	Level{ seed }, readFromFile{ readFromFile }{
#ifdef DEBUG
cout << "Level2 construction starts" << endl;
#endif
	if (readFromFile) {
		this->scriptFile = scriptFile;
		sequence.open(scriptFile);
		string type;
		sequence >> type;
		nextBlock = convertString(type);
	}
}

Colour Level2::chooseNext() {
	int num = rand() % 7;
	if (num == 0) {
		return convertString("S");
	} else if (num == 1) {
		return convertString("Z");
	} else if (num == 2) {
		return convertString("I");
	} else if (num == 3) {
		return convertString("J");
	} else if (num == 4) {
		return convertString("L");
	} else if (num == 5) {
		return convertString("O");
	} else {
		return convertString("T");
	}
}

BlockInfo Level2::generateNextBlock() {
	currBlock = nextBlock;
	if (readFromFile) {
		string type;
		if (!(sequence >> type)) {
			sequence.clear();
			sequence.seekg(0, sequence.beg);
			sequence >> type;
		}
		nextBlock = convertString(type);
	}
	else {
		nextBlock = chooseNext();
	}
	return BlockInfo{ heavy, currBlock };
}

void Level2::setSequence(std::string filename) {
	readFromFile = true;
	scriptFile = filename;
	sequence.open(filename);
	string type;
	sequence >> type;
	nextBlock = convertString(type);
}

int Level2::calculateScore(int rowsCleared) {
	int linesClearScore = rowsCleared + level;
	linesClearScore = linesClearScore * linesClearScore;
	return linesClearScore;
}

void Level2::setRandom() {
	readFromFile = false;
}

