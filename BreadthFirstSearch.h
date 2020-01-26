//
// Created by tom5012 on 20/01/2020.
//

#ifndef MILSTONE2__BREADTHFIRSTSEARCH_H_
#include "Searcher.h"
#define MILSTONE2__BREADTHFIRSTSEARCH_H_

template<typename T>
class BreadthFirstSearch : public Searcher<T> {

  list<State<T>*>* visited;

 public:
  BreadthFirstSearch() { Searcher<T>::evaluatedNodes = 0; }
  virtual ~BreadthFirstSearch() {}
  list<State<T>*>* search(Searchable<T>* matrix) override {

    visited = new list<State<T>*>();

    //pathCost = cost for initial state
    matrix->getInitialState()->setPathCost(matrix->getInitialState()->getCost());

    //mark initial state visited
    visited->push_front(matrix->getInitialState());

    //push initial state to queue
    Searcher<T>::addToQueue(matrix->getInitialState());

    //while queue is not empty
    while (Searcher<T>::queueSize() > 0) {
      State<T>* node = Searcher<T>::popQueue();
      Searcher<T>::evaluatedNodes++;

      //case for initial state that has no parent
      if (node->getParent() != nullptr) {
        node->setPathCost(node->getParent()->getPathCost() + node->getCost());
      }

      //if node is goal state, check backtrace
      if (matrix->isGoalState(node)) {
        list<State<T>*>* retVal = Searcher<T>::backTrace(matrix->getInitialState(), node);
        return retVal;
      }

      //get all successors
      list<State<T>*> successors = matrix->getAllPossibleStates(node);
      for (State<T>* s: successors) {
        if (!isVisited(s)) {
          visited->push_back(s);
          Searcher<T>::addToQueue(s);
        }
      }
    }
    return nullptr;
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

#endif //MILSTONE2__BREADTHFIRSTSEARCH_H_
