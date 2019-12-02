#ifndef _LEVEL1_
#define _LEVEL1_
#include "blockInfo.h"
#include "level.h"
#include <string>
#include <fstream>
#include "colour.h"
#include <sstream>

class Level1 : public Level {
	std::string scriptFile;
	bool readFromFile;
	std::string sequence;

public:
	Level1(int seed,int level, bool readFromFile = false, std::string scriptFile = "");
	Colour chooseNext();
	BlockInfo generateNextBlock() override;
	void setSequence(std::string filename) override;
	int calculateScore(int rowsCleared) override;
	void setRandom() override;
	~Level1();
};


#endif
