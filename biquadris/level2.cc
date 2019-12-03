#include "level2.h"
#include <fstream>
#include "colour.h"
#include "blockInfo.h"
#include <string>

using namespace std;


Level2::Level2(int seed,int level, bool readFromFile, std::string scriptFile) :
	Level{ seed, level}, scriptFile{scriptFile},readFromFile{ readFromFile },sequence {""}{
#ifdef DEBUG
cout << "Level2 construction starts" << endl;
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

void Level2::setSequence(std::string filename) {
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

void Level2::setRandom() {
	readFromFile = false;
}

Level2::~Level2(){
	sequence = "";
	scriptFile = "";
}
