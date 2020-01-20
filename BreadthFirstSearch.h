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
  list<State<T>> search(Searchable<T> problem) override {
    problem.getInitialState().setIsDiscovered(true);
    addToOpenQueue(problem.getInitialState());

    while(Searcher<T>::openQueueSize() > 0){
      State<T> node = Searcher<T>::popOpenQueue();
      if (problem.isGoalState(node)) {
        list<State<T>> retVal = backTrace(problem.getInitialState(),node);
        return retVal;
      }

      list<State<T>> successors = problem.getAllPossibleStates(node);
      for (State<T> s: successors) {
        if(!s.getIsDiscovered()){
          s.setIsDiscovered(true);
          s.setParent(node);
          s.setCost(s.getParent().getCost()+s.getCost());
          addToOpenQueue(s);
        }
      }
    }
    return list<State<T>>();
  }

  list<State<T>> backTrace(State<T> initState, State<T> goalState) {
    Solution solution;
    bool done = false;
    list<State<T>> trace = new ::list<State<T>>();
    trace.push_front(goalState);
    State<T> currentState;
    while (!done) {
      currentState = goalState.getParent();
      trace.push_front(currentState);
      if (initState.equals(currentState)) {
        done = true;
      }
    }
    return trace;
  }
};

#endif //MILSTONE2__BREADTHFIRSTSEARCH_H_
