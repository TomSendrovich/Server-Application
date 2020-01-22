//
// Created by guy on 13/01/2020.
//

#ifndef MILSTONE2__SEARCHABLE_H_
#include <list>
#include <string>
#include "State.h"
using namespace std;
#define MILSTONE2__SEARCHABLE_H_
template<typename T>
class Searchable {

 public:
  virtual State<T>* getInitialState() = 0;
  virtual bool isGoalState(State<T>* state) = 0;
  virtual list<State<T>*> getAllPossibleStates(State<T>* state) = 0;
  virtual string to_string() = 0;
};

#endif //MILSTONE2__SEARCHABLE_H_
