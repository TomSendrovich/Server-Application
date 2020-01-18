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
        //return backTrace();
      }
      list<State<T>> successors = problem.getAllPossibleStates(node);

      for (State<T> s: successors) {

        if (closed.find(s) == closed.end() && !isOpenQueueContains(s)) {
          addToOpenQueue(s);
          //todo set s.parent(node), should be done by "getAllPossibleStates"
        } else {
          //...
        }

      }//end of foreach
    }

    Solution s;
    return s;
  }
};

#endif //MILSTONE2__BESTFIRSTSEARCH_H_
