#ifndef _SPECIALACTION_
#define _SPECIALACTION_

class Board;
class SpecialAction {
    public:
    virtual ~SpecialAction();
	virtual void applySpecialAction(Board&);
};
#endif
