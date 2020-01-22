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
  //BestFirstSearch(Searcher<T>* problem) : Searcher<T>(problem) {}
  BestFirstSearch() {
    Searcher<T>::evaluatedNodes = 0;
    Searcher<T>::openQueue = new priority_queue<State<T>*>();
  }
  list<State<T>*>* search(Searchable<T>* problem) override {
    Searcher<T>::addToOpenQueue(problem->getInitialState());
    unordered_set<State<T>*>* closed = new unordered_set<State<T>*>();

    while (Searcher<T>::openQueueSize() > 0) {
      State<T>* node = Searcher<T>::popOpenQueue();
      closed->insert(node);
      if (problem->isGoalState(node)) {
        list<State<T>*>* retVal = Searcher<T>::backTrace(problem->getInitialState(), node);
        return retVal;
      }
      list<State<T>*> successors = problem->getAllPossibleStates(node);

      for (State<T>* s: successors) {
        if (closed->find(s) == closed->end() && !Searcher<T>::isOpenQueueContains(s)) {// if s not in OPEN or CLOSE
          Searcher<T>::addToOpenQueue(s); ///parent of s was set in getAllPossibleStates
        } else { //found a better path
          if (Searcher<T>::isOpenQueueContains(s)) {
            if (node->getPathCost() + s->getCost() < Searcher<T>::getStateFromQueue(s)->getPathCost()) { //node + s < node in queue
              s->setPathCost(s->getCost() + node->getPathCost());
              Searcher<T>::removeFromOpenQueue(s);
              Searcher<T>::addToOpenQueue(s);
            }
          } else {
            s->setPathCost(s->getCost() + s->getParent()->getPathCost());
            Searcher<T>::addToOpenQueue(s);
          }
        }
      }//end of foreach
    }
  }
};

#endif //MILSTONE2__BESTFIRSTSEARCH_H_
