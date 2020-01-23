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
  DepthFirstSearch() {
    Searcher<T>::evaluatedNodes = 0;
    Searcher<T>::priorityQueue = new priority_queue<State<T>*>();
  }
  list<State<T>*>* search(Searchable<T>* problem) override {
    Searcher<T>::addToPriorityQueue(problem->getInitialState());

    while (Searcher<T>::priorityQueueSize() > 0) {
      State<T>* node = Searcher<T>::popPriorityQueue();

      if (node == problem->getInitialState()) {
        node->setPathCost(node->getCost());
      }

      if (!node->isDiscovered()) { continue; }
      node->setIsDiscovered(true);

      if (problem->isGoalState(node)) {
        list<State<T>*>* retVal = Searcher<T>::backTrace(problem->getInitialState(), node);
        return retVal;
      }

      list<State<T>*> successors = problem->getAllPossibleStates(node);
      for (State<T>* s: successors) {
        if (!s->isDiscovered()) {
          Searcher<T>::addToPriorityQueue(s);
          Searcher<T>::popPriorityQueue();
          return DFS(problem, s);
        }
      }
    }
    return nullptr;
  }

  list<State<T>*>* DFS(Searchable<T>* problem, State<T>* node) {
    node->setIsDiscovered(true);
    node->setPathCost(node->getParent()->getPathCost() + node->getCost());

    if (problem->isGoalState(node)) {
      list<State<T>*>* retVal = Searcher<T>::backTrace(problem->getInitialState(), node);
      return retVal;
    }

    list<State<T>*> successors = problem->getAllPossibleStates(node);
    for (State<T>* s: successors) {
      if (!s->isDiscovered()) {
        Searcher<T>::addToPriorityQueue(s);
        return DFS(problem, s);
      }
    }
  }
};

#endif //MILSTONE2__DEPTHFIRSTSERACH_H_
