//
// Created by tom5012 on 20/01/2020.
//

#ifndef MILSTONE2__BREADTHFIRSTSEARCH_H_
#include "Searcher.h"
#include "Cell.h"
#include <list>
#define MILSTONE2__BREADTHFIRSTSEARCH_H_

template<typename T>
class BreadthFirstSearch : public Searcher<T> {
 public:
  BreadthFirstSearch() {}
  list<State<T>*> search(Searchable<T>* problem) override {
    addToOpenQueue(problem->getInitialState());
    while (Searcher<T>::openQueueSize() > 0) {
      State<T>* node = Searcher<T>::popOpenQueue();
      if (problem->isGoalState(node)) {
        list<State<T>*> retVal = backTrace(problem->getInitialState(), node);
        return retVal;
      }
      if (!node->getIsDiscovered()) {
        node->setIsDiscovered(true);
        if (!node->equals(problem->getInitialState())) {
          node->setCost(node->getParent().getCost() + node->getCost());
        }
        list<State<T>*> successors = problem->getAllPossibleStates(node);
        for (State<T>* s: successors) {
          addToOpenQueue(s);
        }
      }
    }
  }
};

#endif //MILSTONE2__BREADTHFIRSTSEARCH_H_
