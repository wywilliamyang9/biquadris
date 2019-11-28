#ifndef _FORCEBLOCKACTION_
#define _FORCEBLOCKACTION_
#include "colour.h"

class ForceBlockAction: public SpecialAction {
    Colour colour;
    public:
    ForceBlockAction(Colour);
};

#endif 
