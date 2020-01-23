//
// Created by guy on 19/01/2020.
//

#ifndef MILSTONE2__OBJECTADAPTER_H_
#include "Solver.h"
#include "Searcher.h"
#include <iostream>
#define MILSTONE2__OBJECTADAPTER_H_

template<typename P, typename S, typename T>
class ObjectAdapter : public Solver<P, S> {

  Searcher<T>* _searcher;

 public:
  ObjectAdapter(Searcher<T>* searcher) : _searcher(searcher) {}

  S solve(P* problem) override {
    _searcher->resetNumOfEvaluatedNodes();
    Solution solution;
    // Searchable<P>* searchable;
    list<State<T>*>* trace = _searcher->search(problem);

    cout << "number of nodes: " << _searcher->getNumOfEvaluatedNodes() << endl;
    //trace list is ready
    for (typename list<State<T>*>::iterator it = trace->begin(); it != trace->end(); ++it) {
      if (it == trace->begin()) {
        continue;
      }
      string direction = getDirection(*it);
      int pathCost = (*it)->getPathCost();
      string move = direction + " (" + to_string(pathCost) + ")";
      solution.addAction(move);
    }
    string finalSolution = solution.to_string();

    return finalSolution;
  }

  ///return the correct direction depends of the pos of the state and his parent
  string getDirection(State<T>* state) {
    int stateRow = state->getState()->getPosition().first;
    int stateCol = state->getState()->getPosition().second;
    int parentStateRow = state->getParent()->getState()->getPosition().first;
    int parentStateCol = state->getParent()->getState()->getPosition().second;

    if (stateRow - parentStateRow == 1 && stateCol - parentStateCol == 0) { return "Down"; }
    else if (stateRow - parentStateRow == -1 && stateCol - parentStateCol == 0) { return "Up"; }
    else if (stateRow - parentStateRow == 0 && stateCol - parentStateCol == 1) { return "Right"; }
    else if (stateRow - parentStateRow == 0 && stateCol - parentStateCol == -1) { return "Left"; }
    else return "Error";
  }
};

#endif //MILSTONE2__OBJECTADAPTER_H_
