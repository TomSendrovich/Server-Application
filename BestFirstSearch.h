//
// Created by guy on 16/01/2020.
//

#ifndef MILSTONE2__BESTFIRSTSEARCH_H_
#include "Searcher.h"
#define MILSTONE2__BESTFIRSTSEARCH_H_

template<typename T>
class BestFirstSearch : public Searcher<T> {

  list<State<T>*>* closed;

 public:
  BestFirstSearch() {
    Searcher<T>::evaluatedNodes = 0;
  }
  virtual ~BestFirstSearch() {}

  list<State<T>*>* search(Searchable<T>* matrix) override {
    Searcher<T>::addToQueue(matrix->getInitialState());
    closed = new list<State<T>*>();

    while (Searcher<T>::queueSize() > 0) {
      State<T>* node = Searcher<T>::popQueuePathCost();
      Searcher<T>::evaluatedNodes++;

      closed->push_back(node);
      if (matrix->isGoalState(node)) {
        list<State<T>*>* retVal = Searcher<T>::backTrace(matrix->getInitialState(), node);
        return retVal;
      }
      list<State<T>*> successors = matrix->getAllPossibleStates(node);

      for (State<T>* s: successors) {
        if (!isInClosed(s) && !Searcher<T>::isQueueContains(s)) {// if s not in OPEN or CLOSE
          s->setPathCost(s->getCost() + node->getPathCost());
          Searcher<T>::addToQueue(s); ///parent of s was set in getAllPossibleStates
        }
      }//end of foreach
    }
    return nullptr;
  }

  bool isInClosed(State<T>* s) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    bool contains = false;
    while (closed->size() != 0) {
      top = closed->back();
      closed->pop_back();
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
      closed->push_back(tmpVector[i]);
    }
    return contains;
  }
};

#endif //MILSTONE2__BESTFIRSTSEARCH_H_
