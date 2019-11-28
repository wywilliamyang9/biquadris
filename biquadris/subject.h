#ifndef _SUBJECT_
#define _SUBJECT_
#include <vector>

template <typename StateType> class Observer;

template <typename StateType> class Subject {
    std::vector<Observer<StateType>*> observers;
    StateType state;

    public:
    void attach(Observer<StateType> *o);
    void notifyObservers();
    virtual ~Subject() = default;
    virtual StateType getinfo() const = 0;
};

#endif
