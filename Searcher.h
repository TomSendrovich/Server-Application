//
// Created by guy on 13/01/2020.
//

#ifndef MILSTONE2__SEARCHER_H_
#include "Searchable.h"
#include "Solution.h"
#include "State.h"
#include <queue>
#include <unordered_set>
#include <algorithm>
#define MILSTONE2__SEARCHER_H_
template<typename T>
class Searcher {

  int evaluatedNodes;
  Searchable<T> problem;
  priority_queue<State<T>> openQueue;
  //unordered_set<State<T>> closedSet;

 public:
  Searcher(const Searchable<T>& problem) : problem(problem) {
    evaluatedNodes = 0;
    openQueue = new priority_queue<State<T>>();
  }
  virtual list<State<T>> search(Searchable<T> problem) = 0;
  int getNumOfEvaluatedNodes() { return evaluatedNodes; };
  int openQueueSize() { return openQueue.size(); };
  void addToOpenQueue(State<T> state) { openQueue.push(state); }
  State<T> popOpenQueue() {
    evaluatedNodes++;
    return openQueue.pop();
  }
  void removeFromOpenQueue(State<T> state) {
    auto it = find(openQueue->c.begin(), openQueue->c.end(), state);
    if (it != openQueue->c.end()) {
      openQueue->c.erase(it);
      make_heap(openQueue->c.begin(), openQueue->c.end(), openQueue->comp);
    }
  }
  bool isOpenQueueContains(State<T> state) {
    for (typename vector<State<T>>::iterator p = openQueue.begin(); p != openQueue.end(); p++) {
      if (state.equals(p)) {
        return true;
      }
    }
    return false;
  }
  int getStateCost(State<T> state) {
    for (typename vector<State<T>>::iterator p = openQueue.begin(); p != openQueue.end(); p++) {
      if (state.equals(p)) {
        return p.getCost();
      }
    }
    return -1;
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

#endif //MILSTONE2__SEARCHER_H_
