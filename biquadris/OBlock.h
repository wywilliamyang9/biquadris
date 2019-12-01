#ifndef _OBLOCK_
#define _OBLOCK_
#include "block.h"
class Cell;
class Board;
class OBlock : public Block {
	public:
	OBlock(Cell*, Cell*, Cell*, Cell*,
		int heavy, Colour,int);

	void CWRotate(Board&)override;
	void CounterCWRotate(Board&)override;
};

#endif
