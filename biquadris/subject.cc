#include "subject.h"
template <typename StateType>
void Subject<StateType>::attach(Observer<StateType> *o) {
  observers.emplace_back(o);
}

template <typename StateType>
void Subject<StateType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

template <typename StateType>
void Subject<StateType>::setState(StateType newS) { state = newS; }

template <typename StateType>
StateType Subject<StateType>::getState() const { return state; }
#endif