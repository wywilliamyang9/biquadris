//#define DEBUG
#include "level1.h"
#include <fstream>
#include "colour.h"
#include "blockInfo.h"
#include <string>

using namespace std;


Level1::Level1(int seed, int level,bool readFromFile, std::string scriptFile) :
	Level{ seed, level },  scriptFile{scriptFile},readFromFile{ readFromFile },sequence {""}{
#ifdef DEBUG
cout << "Level1 construction starts" << endl;
#endif
	if (readFromFile) {
		fstream fs{scriptFile};
		string type;
		fs >> type;
		nextBlock = convertString(type);

		string currString;
		while (fs >> currString) {
			sequence = sequence + " " + currString;
		}
	} else {
		nextBlock = chooseNext();
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
		currBlock = nextBlock;
		string type;
		string currString;

		if (sequence == "") {
			fstream fs{scriptFile};
			while (fs >> currString) {
				sequence = sequence + " " + currString;
			}
		}

		stringstream ss {sequence};
		ss >> type;
		nextBlock = convertString(type);
		
		sequence = "";
		while (ss >> currString) {
			sequence = sequence + " " + currString;
		}
	}
	else {
		nextBlock = chooseNext();
	}
	return BlockInfo{ heavy, currBlock, false};
}

void Level1::setSequence(std::string filename) {
	scriptFile = filename;

	fstream fs{scriptFile};
	string type;
	fs >> type;
	nextBlock = convertString(type);

	string currString;
	sequence = "";
	while (fs >> currString) {
		sequence = sequence + " " + currString;
	}
}

int Level1::calculateScore(int rowsCleared) {
	int linesClearScore = rowsCleared + level;
	linesClearScore = linesClearScore * linesClearScore;
	return linesClearScore;
}

void Level1::setRandom() {
	readFromFile = false;
}

Level1::~Level1() {
	sequence = "";
	scriptFile = "";
}
