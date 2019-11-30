#ifndef _LEVEL3_
#define _LEVEL3_
#include "blockInfo.h"
#include "level.h"
#include <string>
#include <fstream>
#include "colour.h"

class Level3 : public Level {
	std::string scriptFile;
	bool readFromFile;
	std::fstream sequence;

public:
	Level3(int seed, bool readFromFile = false, std::string scriptFile = "");
	Colour chooseNext();
	BlockInfo generateNextBlock() override;
	void setSequence(std::string filename) override;
	int calculateScore(int rowsCleared) override;
	void setRandom() override;
};


#endif