//
// Created by guy on 16/01/2020.
//

#ifndef MILSTONE2__BESTFIRSTSEARCH_H_
#include "Searcher.h"
#include "Cell.h"
#include <list>
#include <set>
using namespace std;
#define MILSTONE2__BESTFIRSTSEARCH_H_

template<typename T>
class BestFirstSearch : public Searcher<T> {

 public:
  BestFirstSearch() {}
  list<State<T>*> search(Searchable<T>* problem) override {
    addToOpenQueue(problem->getInitialState());
    unordered_set<State<T>> closed = new unordered_set<T>();

    while (Searcher<T>::openQueueSize() > 0) {
      State<T>* node = Searcher<T>::popOpenQueue();
      closed.insert(node);
      if (problem->isGoalState(node)) {
        list<State<T>*> retVal = backTrace(problem->getInitialState(), node);
        return retVal;
      }
      list<State<T>*> successors = problem->getAllPossibleStates(node);

      for (State<T>* s: successors) {
        if (closed.find(s) == closed.end() && !isOpenQueueContains(s)) {// if s not in OPEN or CLOSE
          addToOpenQueue(s); ///parent of s was set in getAllPossibleStates
        } else { //found a better path
          if (isOpenQueueContains(s)) {
            if (node->getPathCost() + s->getCost() < getStateFromQueue(s)->getPathCost()) { //node + s < node in queue
              s->setPathCost(s->getCost() + node->getPathCost());
              removeFromOpenQueue(s);
              addToOpenQueue(s);
            }
          } else {
            s->setPathCost(s->getCost() + s->getParent()->getPathCost());
            addToOpenQueue(s);
          }
        }
      }//end of foreach
    }
  }
};

#endif //MILSTONE2__BESTFIRSTSEARCH_H_
