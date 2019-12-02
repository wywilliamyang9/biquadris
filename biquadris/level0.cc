#include "level0.h"
#include <fstream>

#include "blockInfo.h"
#include <string>

using namespace std;


Level0::Level0(int seed, std::string scriptFile, int level) :
	Level{ seed, level }, scriptFile{ scriptFile }, sequence {""}{
#ifdef DEBUG
cout << "Level0 construction starts" << endl;
#endif
	fstream fs{scriptFile};
	string type;
	fs >> type;
	nextBlock = convertString(type);

	string currString;
	while (fs >> currString) {
		sequence = sequence + currString;
	}
}

BlockInfo Level0::generateNextBlock() {
	currBlock = nextBlock;
	string type;
	string currString;

	if (sequence == "") {
		fstream fs{scriptFile};
		while (fs >> currString) {
			sequence = sequence + currString;
		}
	}

	stringstream ss {sequence};
	ss >> type;
	nextBlock = convertString(type);
	
	sequence = "";
	while (ss >> currString) {
		sequence = sequence + currString;
	}
	return BlockInfo{ heavy,currBlock, false};
}

void Level0::setSequence(std::string filename) {
	scriptFile = filename;

	fstream fs{scriptFile};
	string type;
	fs >> type;
	nextBlock = convertString(type);

	string currString;
	sequence = "";
	while (fs >> currString) {
		sequence = sequence + currString;
	}
}

int Level0::calculateScore(int rowsCleared) {
	int linesClearScore = rowsCleared + level;
	linesClearScore = linesClearScore * linesClearScore;
	return linesClearScore;
}

void Level0::setRandom() {}

Level0::~Level0(){}
