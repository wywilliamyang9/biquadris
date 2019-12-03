#ifndef _SUBJECT_
#define _SUBJECT_
#include <vector>
#include "info.h"
#include <iostream>
class Observer;

class Subject {
    protected:
    std::vector<Observer*> observers;
    Info state;
    bool cleared = false;

    public:
    //void attach(Observer<StateType> *o);
    void attach(Observer *o);
    void dettach(Observer *o);

    void notifyObservers();
    virtual ~Subject() = default;
    virtual Info getinfo() const = 0;
    void setCleared(bool);
    bool getCleared();
};

#endif
