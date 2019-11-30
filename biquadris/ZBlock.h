#ifndef _ZBLOCK_
#define _ZBLOCK_
#include "block.h"
#include "cell.h"

class Board;
class ZBlock : public Block {
public:
	ZBlock(Cell*, Cell*, Cell*, Cell*,
		int heavy, Colour);

	void CWRotate(Board&)override;
	void CounterCWRotate(Board&)override;
};

#endif
