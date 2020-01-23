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
  BreadthFirstSearch() {
    Searcher<T>::evaluatedNodes = 0;
    Searcher<T>::openQueue = new priority_queue<State<T>*>();
  }
  list<State<T>*>* search(Searchable<T>* problem) override {
    Searcher<T>::addToOpenQueue(problem->getInitialState());

    while (Searcher<T>::openQueueSize() > 0) {
      State<T>* node = Searcher<T>::popOpenQueue();

      if (node->isDiscovered()) { continue; }
      node->setIsDiscovered(true);

      if (problem->isGoalState(node)) {
        node->setPathCost(node->getParent()->getPathCost() + node->getCost());
        list<State<T>*>* retVal = Searcher<T>::backTrace(problem->getInitialState(), node);
        return retVal;
      }

      if (node != problem->getInitialState()) {
        node->setPathCost(node->getParent()->getPathCost() + node->getCost());
      } else {
        node->setPathCost(node->getCost());
      }

      list<State<T>*> successors = problem->getAllPossibleStates(node);
      for (State<T>* s: successors) {
        s->setParent(node);
        Searcher<T>::addToOpenQueue(s);
      }

    }
  }
};

#endif //MILSTONE2__BREADTHFIRSTSEARCH_H_
