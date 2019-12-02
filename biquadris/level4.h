#ifndef _LEVEL4_
#define _LEVEL4_
#include "blockInfo.h"
#include "level.h"
#include <string>
#include <fstream>
#include "colour.h"

class Level4 : public Level {
	std::string scriptFile;
	bool readFromFile;
	std::fstream sequence;
	int dotCount;
public:
	Level4(int seed,int level, bool readFromFile = false, std::string scriptFile = "");
	Colour chooseNext();
	BlockInfo generateNextBlock() override;
	void setSequence(std::string filename) override;
	int calculateScore(int rowsCleared) override;
	void setRandom() override;
	void dotCountAddOne();
	~Level4();
};

#endif
