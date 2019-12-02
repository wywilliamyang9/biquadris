#ifndef _DOTBLOCK_
#define _DOTBLOCK_
#include "block.h"
class Cell;
class Board;
class DotBlock : public Block {
public:
	JBlock(Cell*, Cell*, Cell*, Cell*,
		int heavy, Colour,int);

	void CWRotate(Board&)override;
	void CounterCWRotate(Board&)override;
};

#endif
