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
  //todo implement algorithm
  Solution Search(Searchable<T> problem) override {
    addToOpenQueue(problem.getInitialState());
    unordered_set<T> closed = new unordered_set<T>();

    while (Searcher<T>::openQueueSize() > 0) {
      State<T> node = Searcher<T>::popOpenQueue();
      closed.insert(node);
      if (problem.isGoalState(node)) {
        Solution s = backTrace();
        return s;
      }
      list<State<T>> successors = problem.getAllPossibleStates(node);

      for (State<T> s: successors) {
        if (closed.find(s) == closed.end() && !isOpenQueueContains(s)) {// if s not in OPEN or CLOSE
          addToOpenQueue(s); //parent of s was set in getAllPossibleStates
        } else {
          if (s.getParent().getCost() > node.getCost()) {//found a better path
            if (isOpenQueueContains(s)) {
              s.setCost(node.getCost() + s.getCost());
              removeFromOpenQueue(s);
              addToOpenQueue(s);
            } else {
              s.setCost(s.getParent().getCost() + s.getCost());
              addToOpenQueue(s);
            }
          }
        }
      }//end of foreach
    }
  }

  Solution backTrace() {
    //todo implement
  }
};

#endif //MILSTONE2__BESTFIRSTSEARCH_H_
