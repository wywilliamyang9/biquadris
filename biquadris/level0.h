#ifndef _LEVEL0_
#define _LEVEL0_
#include "blockInfo.h"
#include  "level.h"
#include <string>
#include <fstream>
class Level0 : public Level {
	std::string scriptFile;
	std::fstream sequence;
public:
	Level0(int seed, std::string scriptFile);
	BlockInfo generateNextBlock() override;
	void setSequence(std::string filename) override;
	int calculateScore(int rowsCleared) override;
	void setRandom() override;
};


#endif
