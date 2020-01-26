//
// Created by tom5012 on 20/01/2020.
//

#ifndef MILSTONE2__DEPTHFIRSTSERACH_H_
#include "Searcher.h"
#define MILSTONE2__DEPTHFIRSTSERACH_H_

template<typename T>
class DepthFirstSearch : public Searcher<T> {

  list<State<T>*>* visited;
  list<State<T>*>* trace;

 public:
  DepthFirstSearch() { Searcher<T>::evaluatedNodes = 0; }
  virtual ~DepthFirstSearch() {}
  list<State<T>*>* search(Searchable<T>* matrix) override {
    visited = new list<State<T>*>();

    //pathCost = cost for initial state
    matrix->getInitialState()->setPathCost(matrix->getInitialState()->getCost());

    DFS(matrix, matrix->getInitialState());

    ///until here
    return trace;
  }

  void DFS(Searchable<T>* problem, State<T>* node) {
    Searcher<T>::evaluatedNodes++;
    visited->push_back(node);

    //case for initial state that has no parent
    if (node->getParent() != nullptr) {
      node->setPathCost(node->getParent()->getPathCost() + node->getCost());
    }

    //if node is goal state, check backtrace
    if (problem->isGoalState(node)) {
      trace = Searcher<T>::backTrace(problem->getInitialState(), node);
      return;
    }

    //get all successors
    list<State<T>*> successors = problem->getAllPossibleStates(node);
    for (State<T>* s: successors) {
      if (!isVisited(s)) {
        DFS(problem, s);
      }
    }
  }

  bool isVisited(State<T>* s) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    bool contains = false;
    while (!visited->empty()) {
      top = visited->back();
      visited->pop_back();
      tmpVector.push_back(top);

      int topR = top->getState()->getRow();
      int topC = top->getState()->getCol();
      int sR = s->getState()->getRow();
      int sC = s->getState()->getCol();

      if (topR == sR && topC == sC) {
        contains = true;
      }
    }
    // return the states to the queue
    int size = tmpVector.size();
    for (int i = 0; i < size; i++) {
      visited->push_back(tmpVector[i]);
    }
    return contains;
  }

};

#endif //MILSTONE2__DEPTHFIRSTSERACH_H_
