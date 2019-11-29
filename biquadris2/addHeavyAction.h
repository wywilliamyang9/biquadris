#ifndef _ADDHEAVYACTION_
#define _ADDHEAVYACTION_
#include "specialAction.h"
class Board;
class AddHeavyAction: public SpecialAction {
public:
	void applySpecialAction(Board&) override;
};

#endif 
