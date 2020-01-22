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

 protected:
  int evaluatedNodes;
  Searchable<T>* problem;
  priority_queue<State<T>*>* openQueue;

 public:
  /*Searcher(Searchable<T>* problem) : problem(problem) {
    evaluatedNodes = 0;
    openQueue = new priority_queue<State<T>>();
  }*/
  virtual list<State<T>*>* search(Searchable<T>* problem) = 0;
  int getNumOfEvaluatedNodes() { return evaluatedNodes; };
  int openQueueSize() { return openQueue->size(); };
  void addToOpenQueue(State<T>* state) { openQueue->push(state); }
  State<T>* popOpenQueue() {
    State<T>* element = openQueue->top();
    openQueue->pop();
    evaluatedNodes++;
    return element;
  }
  void removeFromOpenQueue(State<T>* state) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    while (openQueueSize() != 0) {
      top = popOpenQueue();
      if (top == state) {
        break;
      }
      tmpVector.push_back(top);
    }
    // return the states to the queue
    int size = tmpVector.size();
    for (int i = 0; i < size; i++) {
      addToOpenQueue(tmpVector[i]);
    }
  }
  bool isOpenQueueContains(State<T>* state) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    bool contains = false;
    while (openQueueSize() != 0) {
      top = popOpenQueue();
      tmpVector.push_back(top);
      if (top == state) {
        contains = true;
      }
    }
    // return the states to the queue
    int size = tmpVector.size();
    for (int i = 0; i < size; i++) {
      addToOpenQueue(tmpVector[i]);
    }
    return contains;
  }
  State<T>* getStateFromQueue(State<T>* state) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    State<T>* retVal = nullptr;
    while (openQueueSize() != 0) {
      top = popOpenQueue();
      tmpVector.push_back(top);
      if (top == state) {
        retVal = top;
      }
    }
    // return the states to the queue
    int size = tmpVector.size();
    for (int i = 0; i < size; i++) {
      addToOpenQueue(tmpVector[i]);
    }
    return retVal;
  }
  list<State<T>*>* backTrace(State<T>* initState, State<T>* goalState) {
    Solution solution;
    bool done = false;
    list<State<T>*>* trace = new list<State<T>*>();
    trace->push_front(goalState);
    State<T>* currentState;
    while (!done) {
      currentState = goalState->getParent();
      trace->push_front(currentState);
      if (initState == currentState) {
        done = true;
      }
    }
    return trace;
  }
};

#endif //MILSTONE2__SEARCHER_H_
