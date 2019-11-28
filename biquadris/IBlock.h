#ifndef _IBLOCK_
#define _IBLOCK_
#include "block.h"

class IBlock: public Block {
    public:
    IBlock (Cell*, Cell*, Cell*, Cell*,
        int heavy, Colour);

    void CWRotate(Board &)override;
    void CounterCWRotate(Board &)override;
}

#endif
