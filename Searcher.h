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
    State<T>* element = priorityQueue.top();
    priorityQueue.pop();
    evaluatedNodes++;
    return element;
  }
  void removeFromPriorityQueue(State<T>* state) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    while (priorityQueueSize() != 0) {
      top = popPriorityQueue();
      if (top == state) {
        break;
      }
      tmpVector.push_back(top);
    }
    // return the states to the queue
    int size = tmpVector.size();
    for (int i = 0; i < size; i++) {
      addToPriorityQueue(tmpVector[i]);
    }
  }
  bool isPriorityQueueContains(State<T>* state) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    bool contains = false;
    while (priorityQueueSize() != 0) {
      top = popPriorityQueue();
      tmpVector.push_back(top);
      if (top == state) {
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
      tmpVector.push_back(top);
      if (top == state) {
        retVal = top;
      }
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
    State<T>* element = queue.top();
    queue.pop();
    evaluatedNodes++;
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
