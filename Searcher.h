//
// Created by guy on 13/01/2020.
//

#ifndef MILSTONE2__SEARCHER_H_
#include "Searchable.h"
#include "Solution.h"
#include "State.h"
#include <queue>
#define MILSTONE2__SEARCHER_H_

template<typename T>
class StateComparator {
 public:
  int operator()(State<T>* s1, State<T>* s2) {
    return s1->getCost() > s2->getCost();
  }
};

template<typename T>
class Searcher {

 protected:
  int evaluatedNodes;
  Searchable<T>* problem;
  priority_queue<State<T>*, vector<State<T>*>, StateComparator<T>> priorityQueue;
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
      if (initState == currentState) {
        done = true;
      }
    }
    return trace;
  }

  ///priority queue methods
  int priorityQueueSize() { return priorityQueue.size(); };
  void addToPriorityQueue(State<T>* state) { priorityQueue.push(state); }
  State<T>* popPriorityQueue() {
    int minPathCost = priorityQueue.top()->getPathCost();
    int elementPathCost;
    State<T>* minState = priorityQueue.top();

    vector<State<T>*> tmpVector;
    State<T>* element;
    while (priorityQueueSize() != 0) {
      element = priorityQueue.top();
      priorityQueue.pop();

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
        addToPriorityQueue(tmpVector[i]);
      }
    }

    return minState;
  }
  State<T>* popPriorityQueueHeuristic() {
    int minHeuristic = priorityQueue.top()->getHeuristicCost();
    int elementHeuristic;
    State<T>* minState = priorityQueue.top();

    vector<State<T>*> tmpVector;
    State<T>* element;
    while (priorityQueueSize() != 0) {
      element = priorityQueue.top();
      priorityQueue.pop();

      elementHeuristic = element->getPathCost();

      if (elementHeuristic < minHeuristic) {
        minState = element;
        minHeuristic = elementHeuristic;
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
        addToPriorityQueue(tmpVector[i]);
      }
    }

    return minState;
  }
  /*void removeFromPriorityQueue(State<T>* state) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    while (priorityQueueSize() != 0) {
      top = popPriorityQueue();

      int topR = top->getState()->getRow();
      int topC = top->getState()->getCol();
      int sR = state->getState()->getRow();
      int sC = state->getState()->getCol();

      if (topR == sR && topC == sC) {
        break;
      }
      tmpVector.push_back(top);
    }
    // return the states to the queue
    int size = tmpVector.size();
    for (int i = 0; i < size; i++) {
      addToPriorityQueue(tmpVector[i]);
    }
  }*/
  bool isPriorityQueueContains(State<T>* state) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    bool contains = false;
    while (priorityQueueSize() != 0) {
      top = popPriorityQueue();
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
      addToPriorityQueue(tmpVector[i]);
    }
    return contains;
  }
  State<T>* getStateFromPriorityQueue(State<T>* state) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    State<T>* retVal = nullptr;
    while (priorityQueueSize() != 0) {
      top = popPriorityQueue();

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
      addToPriorityQueue(tmpVector[i]);
    }
    return retVal;
  }

  ///regular queue methods
  int queueSize() { return queue.size(); };
  void addToQueue(State<T>* state) { queue.push(state); }
  State<T>* popQueue() {
    State<T>* element = queue.front();
    queue.pop();
    return element;
  }
  void removeFromQueue(State<T>* state) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    while (queueSize() != 0) {
      top = popQueue();
      if (top == state) {
        break;
      }
      tmpVector.push_back(top);
    }
    // return the states to the queue
    int size = tmpVector.size();
    for (int i = 0; i < size; i++) {
      addToQueue(tmpVector[i]);
    }
  }
  bool isQueueContains(State<T>* state) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    bool contains = false;
    while (queueSize() != 0) {
      top = popQueue();
      tmpVector.push_back(top);
      if (top == state) {
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
  State<T>* getStateFromQueue(State<T>* state) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    State<T>* retVal = nullptr;
    while (queueSize() != 0) {
      top = popPriorityQueue();
      tmpVector.push_back(top);
      if (top == state) {
        retVal = top;
      }
    }
    // return the states to the queue
    int size = tmpVector.size();
    for (int i = 0; i < size; i++) {
      addToQueue(tmpVector[i]);
    }
    return retVal;
  }
};

#endif //MILSTONE2__SEARCHER_H_
