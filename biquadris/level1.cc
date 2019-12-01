//#define DEBUG
#include "level1.h"
#include <fstream>
#include "colour.h"
#include "blockInfo.h"
#include <string>

using namespace std;


Level1::Level1(int seed, bool readFromFile, std::string scriptFile) :
	Level{ seed }, readFromFile{ readFromFile }{
#ifdef DEBUG
cout << "Level1 construction starts" << endl;
#endif
	if (readFromFile) {
		this->scriptFile = scriptFile;
		sequence.open(scriptFile);
		string type;
		sequence >> type;
		nextBlock = convertString(type);
	}
}

Colour Level1::chooseNext() {
	int num = rand() % 12;
	if (num == 0) {
		return convertString("S");
	} else if (num == 1) {
		return convertString("Z");
	} else if (num == 2 || num == 3) {
		return convertString("I");
	} else if (num == 4 || num == 5) {
		return convertString("J");
	} else if (num == 6 || num == 7) {
		return convertString("L");
	} else if (num == 8 || num == 9) {
		return convertString("O");
	} else {
		return convertString("T");
	}
}

BlockInfo Level1::generateNextBlock() {
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

void Level1::setSequence(std::string filename) {
	readFromFile = true;
	scriptFile = filename;
	sequence.open(filename);
	string type;
	sequence >> type;
	nextBlock = convertString(type);
}

int Level1::calculateScore(int rowsCleared) {
	int linesClearScore = rowsCleared + level;
	linesClearScore = linesClearScore * linesClearScore;
	return linesClearScore;
}

void Level1::setRandom() {
	readFromFile = false;
}

