//#define DEBUG
#include "subject.h"
#include "observer.h"
using namespace std;
void Subject::attach(Observer *o) {
  observers.emplace_back(o);
}

void Subject::notifyObservers() {
  for (auto &ob : observers){
    #ifdef DEBUG
    cout << "notifying" << endl;
    #endif
    ob->notify(*this);
  }
}

Info Subject::getinfo() const { return state; }

