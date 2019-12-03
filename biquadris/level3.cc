#include "level3.h"
#include <fstream>
#include "colour.h"
#include "blockInfo.h"
#include <string>

using namespace std;


Level3::Level3(int seed, int level,bool readFromFile, std::string scriptFile) :
	Level{ seed, level}, scriptFile{scriptFile},readFromFile{ readFromFile },sequence {""}{
#ifdef DEBUG
cout << "Level3 construction starts" << endl;
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
	}else {
		nextBlock = chooseNext();
	}
}

Colour Level3::chooseNext() {
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

BlockInfo Level3::generateNextBlock() {
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
	heavy++;
	return BlockInfo{ heavy, currBlock, false};
}

void Level3::setSequence(std::string filename) {
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

int Level3::calculateScore(int rowsCleared) {
	if (rowsCleared == 0) return 0;
	int linesClearScore = rowsCleared + level;
	linesClearScore = linesClearScore * linesClearScore;
	return linesClearScore;
}

void Level3::setRandom() {
	readFromFile = false;
}

Level3::~Level3(){
	sequence = "";
	scriptFile = "";
}
