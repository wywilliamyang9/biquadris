#ifndef _OBLOCK_
#define _OBLOCK_
#include "block.h"
#include "cell.h"

class Board;
class OBlock : public Block {
	public:
	OBlock(Cell*, Cell*, Cell*, Cell*,
		int heavy, Colour);

	void CWRotate(Board&)override;
	void CounterCWRotate(Board&)override;
};

#endif
