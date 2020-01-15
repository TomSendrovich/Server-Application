//
// Created by guy on 13/01/2020.
//

#ifndef MILSTONE2__SEARCHABLE_H_
#include <vector>
#include "State.h"
using namespace std;
#define MILSTONE2__SEARCHABLE_H_
template<typename T>
class Searchable {
  State<T> getInitialState() = 0;
  bool isGoalState(State<T> state) = 0;
  vector<State<T>> getAllPossibleStates(State<T> state) = 0;
};

#endif //MILSTONE2__SEARCHABLE_H_
