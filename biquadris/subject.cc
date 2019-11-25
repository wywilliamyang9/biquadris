#include "subject.h"
template <typename InfoType>
void Subject<InfoType>::attach(Observer<InfoType> *o) {
  observers.emplace_back(o);
}

template <typename InfoType>
void Subject<InfoType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

template <typename InfoType>
void Subject<InfoType>::setState(StateType newS) { state = newS; }

template <typename InfoType>
StateType Subject<InfoType>::getState() const { return state; }
#endif
