#ifndef _OBSERVER_
#define _OBSERVER_

template <typename StateType> class Observer;

template <typename StateType> class Subject {
    std::vector<Observer<StateType>*> observers;
    StateType state;

    public:
    void attach(Observer<StateType> *o);
    void notifyObservers();
    virtual ~Observer() = default;
    virtual StateType getinfo() const = 0;
};

#endif
