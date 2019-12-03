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

void Subject::dettach(Observer *o) {
  for (int i = 0; (unsigned)i < observers.size(); ++i) {
    if (observers.at(i) == o) {
      observers.erase (observers.begin() + i);
      return;
    }
  }
  cout << "dettach failed! " << endl;
}

void Subject::setCleared(bool b) {cleared = b;}
bool Subject::getCleared() {return cleared;}
