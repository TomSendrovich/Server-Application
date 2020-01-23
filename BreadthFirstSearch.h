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
  BreadthFirstSearch() { Searcher<T>::evaluatedNodes = 0; }
  list<State<T>*>* search(Searchable<T>* problem) override {
    Searcher<T>::addToQueue(problem->getInitialState());
    auto* discoveredNodes = new list<State<T>*>;
    bool isDiscovered = false;

    while (Searcher<T>::queueSize() > 0) {
      State<T>* node = Searcher<T>::popQueue();
      typename list<State<T>*>::iterator it = discoveredNodes->begin();
      for (int i = 0; i < discoveredNodes->size(); i++) {
        State<T>* currentNode = *it;
        if (currentNode->operator==(node)) {
          isDiscovered = true;
        }
        it++;
      }
      if (isDiscovered) {
        isDiscovered = false;
        continue;
      }
      discoveredNodes->push_front(node);

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
        Searcher<T>::addToQueue(s);
      }

    }
  }
};

#endif //MILSTONE2__BREADTHFIRSTSEARCH_H_
