#ifndef _OBSERVER_
#define _OBSERVER_

template <typename StateType> class Subject;

template <typename StateType> class Observer {
    public:
    virtual void notify(Subject<StateType> &caller) = 0;
    virtual ~Observer() = default;
};

#endif