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
	Colour chooseNext();

public:
	Level1(int seed,int level, bool readFromFile = false, std::string scriptFile = "");
	BlockInfo generateNextBlock() override;
	void setSequence(std::string filename) override;
	void setRandom() override;
	~Level1();
};


#endif
