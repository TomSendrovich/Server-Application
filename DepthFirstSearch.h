//
// Created by tom5012 on 20/01/2020.
//

#ifndef MILSTONE2__DEPTHFIRSTSERACH_H_
#include "Searcher.h"
#include "Cell.h"
#include <list>
#define MILSTONE2__DEPTHFIRSTSERACH_H_

template<typename T>
class DepthFirstSearch : public Searcher<T> {

  list<State<T>*>* visited;

 public:
  DepthFirstSearch() { Searcher<T>::evaluatedNodes = 0; }
  list<State<T>*>* search(Searchable<T>* problem) override {
    visited = new list<State<T>*>();

    Searcher<T>::addToQueue(problem->getInitialState());

    while (Searcher<T>::queueSize() > 0) {
      State<T>* node = Searcher<T>::popQueue();

      //handle the first node
      if (node == problem->getInitialState()) {
        node->setPathCost(node->getCost());
      }

      //if node was visited, pass him
      if (isVisited(node)) {
        continue;
      }
      visited->push_back(node);

      if (problem->isGoalState(node)) {
        list<State<T>*>* retVal = Searcher<T>::backTrace(problem->getInitialState(), node);
        return retVal;
      }

      list<State<T>*> successors = problem->getAllPossibleStates(node);
      for (State<T>* s: successors) {
        if (!isVisited(s)) {
          Searcher<T>::queue.push(s);
          State<T>* sFromQueue = Searcher<T>::queue.back();
          Searcher<T>::evaluatedNodes++;
          return DFS(problem, sFromQueue);
        }
      }
    }
    return nullptr;
  }

  list<State<T>*>* DFS(Searchable<T>* problem, State<T>* node) {
    visited->push_back(node);
    node->setPathCost(node->getParent()->getPathCost() + node->getCost());

    if (problem->isGoalState(node)) {
      list<State<T>*>* retVal = Searcher<T>::backTrace(problem->getInitialState(), node);
      return retVal;
    }

    list<State<T>*> successors = problem->getAllPossibleStates(node);
    for (State<T>* s: successors) {
      if (!isVisited(s)) {
        Searcher<T>::queue.push(s);
        State<T>* sFromQueue = Searcher<T>::queue.back();
        Searcher<T>::evaluatedNodes++;
        return DFS(problem, sFromQueue);
      }
    }
  }

  bool isVisited(State<T>* s) {
    vector<State<T>*> tmpVector;
    State<T>* top;
    bool contains = false;
    while (!visited->empty()) {
      top = visited->back();
      visited->pop_back();
      tmpVector.push_back(top);

      int topR = top->getState()->getRow();
      int topC = top->getState()->getCol();
      int sR = s->getState()->getRow();
      int sC = s->getState()->getCol();

      if (topR == sR && topC == sC) {
        contains = true;
      }
    }
    // return the states to the queue
    int size = tmpVector.size();
    for (int i = 0; i < size; i++) {
      visited->push_back(tmpVector[i]);
    }
    return contains;
  }

};

#endif //MILSTONE2__DEPTHFIRSTSERACH_H_
