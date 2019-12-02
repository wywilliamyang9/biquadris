#ifndef _DOTBLOCK_
#define _DOTBLOCK_
#include "block.h"
class Cell;
class Board;
class DotBlock : public Block {
public:
	DotBlock(Cell*);

	void CWRotate(Board&)override;
	void CounterCWRotate(Board&)override;
};

#endif
