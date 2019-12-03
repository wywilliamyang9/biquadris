#ifndef _LEVEL4_
#define _LEVEL4_
#include "blockInfo.h"
#include "level.h"
#include <string>
#include <fstream>
#include "colour.h"
#include <sstream>

class Level4 : public Level {
	std::string scriptFile;
	bool readFromFile;
	std::string sequence;
	int dotCount;
	Colour chooseNext();
	void dotCountAddOne();

public:
	Level4(int seed,int level, bool readFromFile = false, std::string scriptFile = "");
	BlockInfo generateNextBlock() override;
	void setSequence(std::string filename) override;
	void setRandom() override;
	~Level4();
};

#endif
