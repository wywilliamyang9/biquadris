#ifndef _LEVEL2_
#define _LEVEL2_
#include "blockInfo.h"
#include "level.h"
#include <string>
#include <fstream>
#include "colour.h"

class Level2 : public Level {
	std::string scriptFile;
	bool readFromFile;
	std::fstream sequence;

public:
	Level2(int seed, int level,bool readFromFile = false, std::string scriptFile = "");
	Colour chooseNext();
	BlockInfo generateNextBlock() override;
	void setSequence(std::string filename) override;
	int calculateScore(int rowsCleared) override;
	void setRandom() override;
	~Level2();
};


#endif
