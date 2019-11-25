#ifndef _OBSERVER_
#define _OBSERVER_

template <typename StateType> class Observer;

template <typename StateType> class Subject {
    std::vector<Observer<StateType>*> observers;
    StateType state;

    protected:
    void setState(StateType newS);

    public:
    void attach(Observer<StateType> *o);
    virtual ~Observer() = default;
    virtual StateType getinfo() const;
};

#endif
