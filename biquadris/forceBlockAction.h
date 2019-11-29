#ifndef _FORCEBLOCKACTION_
#define _FORCEBLOCKACTION_
#include "colour.h"
#include "specialAction.h"
class Board;

class ForceBlockAction: public SpecialAction {
    Colour colour;
    public:
    ForceBlockAction(Colour);
	void applySpecialAction(Board&) override;
};

#endif 
