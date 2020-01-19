//
// Created by guy on 16/01/2020.
//

#ifndef MILSTONE2__MATRIXPROBLEM_H_
#include <vector>
#include <string>
#include <list>
#include "Searchable.h"
#include "Cell.h"
using namespace std;
#define MILSTONE2__MATRIXPROBLEM_H_

template<typename T>
class MatrixProblem : public Searchable<T> {

  vector<vector<string>> data;
  State<T> initState, goalState;
  int size;

 public:

  MatrixProblem(const vector<vector<string>>& data, const State<T>& init_state, const State<T>& goal_state, int size)
      : data(data), initState(init_state), goalState(goal_state), size(size) {}

  State<T> getInitialState() override { return initState; }
  bool isGoalState(State<T> state) override { return state == goalState; }
  State<T> getGoalState() { return goalState; }
  list<State<T>> getAllPossibleStates(State<T> state) override {

    list<State<T>> list = new ::list<State<T>>();

    int row = state.getState().getPosition.getRow();
    int col = state.getState().getPosition.getCol();

    if (isValidPosition(row - 1, col - 1)) {
      pushToList(row - 1, col - 1, state, list);
    }
    if (isValidPosition(row - 1, col)) {
      pushToList(row - 1, col, state, list);
    }
    if (isValidPosition(row - 1, col + 1)) {
      pushToList(row - 1, col + 1, state, list);
    }
    if (isValidPosition(row, col - 1)) {
      pushToList(row, col - 1, state, list);
    }
    if (isValidPosition(row, col + 1)) {
      pushToList(row, col + 1, state, list);
    }
    if (isValidPosition(row + 1, col - 1)) {
      pushToList(row + 1, col - 1, state, list);
    }
    if (isValidPosition(row + 1, col)) {
      pushToList(row + 1, col, state, list);
    }
    if (isValidPosition(row + 1, col + 1)) {
      pushToList(row + 1, col + 1, state, list);
    }

    return list;
  }
  void pushToList(int row, int col, State<T> state, list<State<T>>& list) {
    Position* pos = new Position(row, col);
    int value = atoi(data[row][col].c_str());
    Cell* c = new Cell(pos, value);
    State<T> successor = new State<T>(c);
    successor.setParent(state);
    successor.setCost(value);
    list.push_front(successor);
  }
  bool isValidPosition(int row, int col) { return !(row == -1 || row == size || col == -1 || col == size); }
  string to_string() { return "MatrixProblem"; }

};

#endif //MILSTONE2__MATRIXPROBLEM_H_
