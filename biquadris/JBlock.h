#ifndef _JBLOCK_
#define _JBLOCK_
#include "block.h"
#include "cell.h"

class Board;
class JBlock : public Block {
public:
	JBlock(Cell*, Cell*, Cell*, Cell*,
		int heavy, Colour);

	void CWRotate(Board&)override;
	void CounterCWRotate(Board&)override;
};

#endif
