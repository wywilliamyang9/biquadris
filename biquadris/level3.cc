#include "level3.h"
#include "block.h"
#include <fstream>
#include "colour.h"
#include "blockInfo.h"
#include <string>

using namespace std;


Level3::Level3(int seed, bool readFromFile, std::string scriptFile) :
	Level{ seed }, readFromFile{ readFromFile }{
	if (readFromFile) {
		this->scriptFile = scriptFile;
		sequence.open(scriptFile);
		string type;
		sequence >> type;
		nextBlock = convertString(type);
	}
}

Colour Level3::chooseNext() {
	int num = rand() % 9;
	if (num == 0 || num == 1) {
		return convertString("S");
	}
	else if (num == 2 || num == 3) {
		return convertString("Z");
	}
	else if (num == 4) {
		return convertString("I");
	}
	else if (num == 5) {
		return convertString("J");
	}
	else if (num == 6) {
		return convertString("L");
	}
	else if (num == 7) {
		return convertString("O");
	}
	else if (num == 8) {
		return convertString("T");
	}
}

BlockInfo Level3::generateNextBlock() {
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

void Level3::setSequence(std::string filename) {
	readFromFile = true;
	scriptFile = filename;
	sequence.open(filename);
	string type;
	sequence >> type;
	nextBlock = convertString(type);
}

int Level3::calculateScore(int rowsCleared) {
	int linesClearScore = rowsCleared + level;
	linesClearScore = linesClearScore * linesClearScore;
	return linesClearScore;
}

void Level3::setRandom() {
	readFromFile = false;
}

