#ifndef _LBLOCK_
#define _LBLOCK_
#include "block.h"
#include "cell.h"

class Board;
class SBlock : public Block {
public:
	SBlock(Cell*, Cell*, Cell*, Cell*,
		int heavy, Colour);

	void CWRotate(Board&)override;
	void CounterCWRotate(Board&)override;
};

#endif
