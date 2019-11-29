#ifndef _BLINDACTION_
#define _BLINDACTION_
#include "specialAction.h"
class Board;
class BlindAction: public SpecialAction {
public:
	void applySpecialAction(Board&) override;
};

#endif 
