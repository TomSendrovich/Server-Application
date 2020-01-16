//
// Created by guy on 16/01/2020.
//

#ifndef MILSTONE2__MATRIXPROBLEM_H_
#include <vector>
#include <string>
#define MILSTONE2__MATRIXPROBLEM_H_

#include "Searchable.h"
template<typename T>
class MatrixProblem : public Searchable<T> {

  vector<vector<int>> data;
  State<T> initState, goalState;

 public:

  MatrixProblem(const vector<vector<int>>& data, const State<T>& initial_state, const State<T>& goal_state)
      : data(data), initState(initial_state), goalState(goal_state) {}

  State<T> getInitialState() override {
    return initState;
  }

  bool isGoalState(State<T> state) override {
    return state == goalState;
  }

  //todo implement
  vector<State<T>> getAllPossibleStates(State<T> state) override {
    return vector<State<T>>();
  }

};

#endif //MILSTONE2__MATRIXPROBLEM_H_
