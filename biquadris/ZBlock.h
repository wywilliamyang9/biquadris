#ifndef _ZBLOCK_
#define _ZBLOCK_
#include "block.h"
class Cell;
class Board;
class ZBlock : public Block {
public:
	ZBlock(Cell*, Cell*, Cell*, Cell*,
		int heavy, Colour,int);

	void CWRotate(Board&)override;
	void CounterCWRotate(Board&)override;
};

#endif
