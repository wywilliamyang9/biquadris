#ifndef _OBSERVER_
#define _OBSERVER_
#include "nextBlock.h"
#include <vector>

class Subject;
class Observer {
    public:
    virtual void notify(Subject &caller) = 0;
    virtual ~Observer() = default;
};
#endif
