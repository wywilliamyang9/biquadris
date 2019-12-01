#ifndef _LBLOCK_
#define _LBLOCK_
#include "block.h"
class Cell;
class Board;
class LBlock : public Block {
public:
	LBlock(Cell*, Cell*, Cell*, Cell*,
		int heavy, Colour,int);

	void CWRotate(Board&)override;
	void CounterCWRotate(Board&)override;
};

#endif
