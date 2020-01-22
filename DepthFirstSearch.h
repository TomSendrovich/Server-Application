//
// Created by tom5012 on 20/01/2020.
//

#ifndef MILSTONE2__DEPTHFIRSTSERACH_H_
#include "Searcher.h"
#include "Cell.h"
#include <list>
#define MILSTONE2__DEPTHFIRSTSERACH_H_

template<typename T>
class DepthFirstSearch : public Searcher<T> {
 public:
  DepthFirstSearch() {}
  list<State<T>*> search(Searchable<T>* problem) override {
    problem->getInitialState()->setIsDiscovered(true);
    addToOpenQueue(problem->getInitialState());

    while (Searcher<T>::openQueueSize() > 0) {
      State<T> node = Searcher<T>::popOpenQueue();
      if (problem->isGoalState(node)) {
        list<State<T>*> retVal = backTrace(problem->getInitialState(), node);
        return retVal;
      }

      list<State<T>*> successors = problem->getAllPossibleStates(node);
      for (State<T>* s: successors) {
        if (!s->getIsDiscovered()) {
          s->setIsDiscovered(true);
          s->setParent(node);
          s->setCost(s->getParent().getCost() + s->getCost());
          addToOpenQueue(s);
        }
      }
    }
    return list<State<T>>();
  }

};

#endif //MILSTONE2__DEPTHFIRSTSERACH_H_
