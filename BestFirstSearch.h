//
// Created by guy on 16/01/2020.
//

#ifndef MILSTONE2__BESTFIRSTSEARCH_H_
#include "Searcher.h"
#include <queue>
#include <set>
#define MILSTONE2__BESTFIRSTSEARCH_H_

template<typename T, typename S>
class BestFirstSearch : public Searcher<T, S> {

  priority_queue<State<T>> openQueue;
  set<State<T>> closedSet;

 public:

  //todo implement algorithm
  S Search(Searchable<T> searchable) override {
    while (!openQueue.empty()) {
      State<T> node = openQueue.pop();
      closedSet.insert(node);

      //...continue

    }



    return "";
  }
};

#endif //MILSTONE2__BESTFIRSTSEARCH_H_
