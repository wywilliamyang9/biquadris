#ifndef _SUBJECT_
#define _SUBJECT_
#include <vector>
#include "info.h"
class Observer;

class Subject {
    protected:
    std::vector<Observer*> observers;
    Info state;

    public:
    //void attach(Observer<StateType> *o);
    void attach(Observer *o);

    void notifyObservers();
    virtual ~Subject() = default;
    virtual Info getinfo() const = 0;
};

#endif
