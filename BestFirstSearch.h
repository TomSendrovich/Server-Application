//
// Created by guy on 16/01/2020.
//

#ifndef MILSTONE2__BESTFIRSTSEARCH_H_
#include "Searcher.h"
#include "Cell.h"
#include <queue>
#include <list>
#include <set>
using namespace std;
#define MILSTONE2__BESTFIRSTSEARCH_H_

template<typename T, typename S>
class BestFirstSearch : public Searcher<T> {

  priority_queue<State<Cell>> openQueue;
  set<State<Cell>> closedSet;

 public:

  //todo implement algorithm
  S Search(Searchable<T> problem) override {
   /* openQueue.push(problem.getInitialState());

    while (!openQueue.empty()) {
      State<T> node = openQueue.pop();
      closedSet.insert(node);

      //check if node state is goal state
      if (problem.isGoalState(node)) {
        // backtrace path to node (through recorded parents) and return path
      }

      //get nodes' successors
      auto successors = getNodeSuccessors(node);

      //for each successor s
      for (auto s: successors) {
        if (closedSet.find(s) == closedSet.end()) {

          //if s is not in CLOSED and not in OPEN
          if (openQueue.find(s) == openQueue.end()) {
            //update that we came to s from node
            openQueue.push(s);
          } else { //s is in OPEN

            // if the is better path to s: update s.weight, pop s and push back.

          }
        }

      }//end of foreach
    }*/

    return "";
  }


  list<State<Cell>> getNodeSuccessors(State<T> node) {

  }
};

#endif //MILSTONE2__BESTFIRSTSEARCH_H_
