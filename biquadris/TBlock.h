#ifndef _TBLOCK_
#define _TBLOCK_
#include "block.h"
class Cell;
class Board;
class TBlock : public Block {
public:
	TBlock(Cell*, Cell*, Cell*, Cell*,
		int heavy, Colour,int);

	void CWRotate(Board&)override;
	void CounterCWRotate(Board&)override;
};

#endif
