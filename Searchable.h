//
// Created by guy on 13/01/2020.
//

#ifndef MILSTONE2__SEARCHABLE_H_
#include <vector>
#include "State.h"
#define MILSTONE2__SEARCHABLE_H_
template<typename T>
class Searchable {

 public:
  virtual State<T> getInitialState() = 0;
  virtual bool isGoalState(State<T> state) = 0;
  virtual vector<State<T>> getAllPossibleStates(State<T> state) = 0;
};

#endif //MILSTONE2__SEARCHABLE_H_
