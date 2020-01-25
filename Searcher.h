//
// Created by guy on 13/01/2020.
//

#ifndef MILSTONE2__SEARCHER_H_
#include "Searchable.h"
#include "Solution.h"
#include <queue>
#include <iostream>
#include <limits.h>
#define MILSTONE2__SEARCHER_H_

template<typename T>
class Searcher {

 protected:
  int evaluatedNodes;
  Searchable<T>* problem;
  std::queue<State<T>*> queue;

 public:
  virtual list<State<T>*>* search(Searchable<T>* problem) = 0;
  int getNumOfEvaluatedNodes() { return evaluatedNodes; };
  void resetNumOfEvaluatedNodes() { evaluatedNodes = 0; };
  list<State<T>*>* backTrace(State<T>* initState, State<T>* goalState) {
    Solution solution;
    bool done = false;
    list<State<T>*>* trace = new list<State<T>*>();
    trace->push_front(goalState);
    State<T>* currentState = goalState;
    while (!done) {
      currentState = currentState->getParent();
      trace->push_front(currentState);

      int topR = initState->getState()->getRow();
      int topC = initState->getState()->getCol();
      int sR = currentState->getState()->getRow();
      int sC = currentState->getState()->getCol();

      if (topR == sR && topC == sC) {
        done = true;
      }
    }
    return
        trace;
  }

  State<T>* popQueue() {
    State<T>* element = queue.front();
    queue.pop();
    return element;
  }
  State<T>* popQueuePathCost() {
    int minPathCost = queue.front()->getPathCost();
    int elementPathCost;
    State<T>* minState = queue.front();

    vector<State<T>*> tmpVector;
    State<T>* element;
    while (queueSize() != 0) {
      element = queue.front();
      queue.pop();

      elementPathCost = element->getPathCost();

      if (elementPathCost < minPathCost) {
        minState = element;
        minPathCost = elementPathCost;
      }

      tmpVector.push_back(element);
    }
    // return the states to the queue
    int size = tmpVector.size();
    for (int i = 0; i < size; i++) {
      State<T>* state = tmpVector[i];
      int topR = minState->getState()->getRow();
      int topC = minState->getState()->getCol();
      int sR = state->getState()->getRow();
      int sC = state->getState()->getCol();

      if (topR == sR && topC == sC) {
        continue;
      } else {
        addToQueue(tmpVector[i]);
      }
    }

    return minState;
  }
  State<T>* popQueueHeuristic() {
    int f, g, h;
    int minF = INT_MAX;
    int elementHeuristic;
    State<T>* minState = queue.front();

    vector<State<T>*> tmpVector;
    State<T>* element;
    while (queueSize() != 0) {
      element = queue.front();
      queue.pop();
      tmpVector.push_back(element);

      h = element->getHeuristicCost();
      g = element->getPathCost();
      f = g + h;

      if (f < minF) {
        minF = f;
        minState = element;
      }

    }
    // return the states to the queue
    int size = tmpVector.size();
    for (int i = 0; i < size; i++) {
      State<T>* state = tmpVector[i];
      int topR = minState->getState()->getRow();
      int topC = minState->getState()->getCol();
      int sR = state->getState()->getRow();
      int sC = state->getState()->getCol();

      if (topR == sR && topC == sC) {
        continue;
      } else {
        addToQueue(tmpVector[i]);
      }
    }

    return minState;
  }
  State<T>* getStateFromQueue(State<T>* state) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    State<T>* retVal = nullptr;
    while (queueSize() != 0) {
      top = popQueue();

      int topR = top->getState()->getRow();
      int topC = top->getState()->getCol();
      int sR = state->getState()->getRow();
      int sC = state->getState()->getCol();

      if (topR == sR && topC == sC) {
        retVal = top;
        break;
      }
      tmpVector.push_back(top);

    }
    // return the states to the queue
    int size = tmpVector.size();
    for (int i = 0; i < size; i++) {
      addToQueue(tmpVector[i]);
    }
    return retVal;
  }
  bool isQueueContains(State<T>* state) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    bool contains = false;
    while (queueSize() != 0) {
      top = popQueue();
      tmpVector.push_back(top);

      int topR = top->getState()->getRow();
      int topC = top->getState()->getCol();
      int sR = state->getState()->getRow();
      int sC = state->getState()->getCol();

      if (topR == sR && topC == sC) {
        contains = true;
      }
    }
    // return the states to the queue
    int size = tmpVector.size();
    for (int i = 0; i < size; i++) {
      addToQueue(tmpVector[i]);
    }
    return contains;
  }
  int queueSize() { return queue.size(); };
  void addToQueue(State<T>* state) { queue.push(state); }

};

#endif //MILSTONE2__SEARCHER_H_
