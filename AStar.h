//
// Created by guy on 24/01/2020.
//

#ifndef MILSTONE2__ASTAR_H_
#include "Searcher.h"
#define MILSTONE2__ASTAR_H_

template<typename T>
class AStar : public Searcher<T> {

  list<State<T>*>* visited;

 public:
  AStar() { Searcher<T>::evaluatedNodes = 0; }
  virtual ~AStar() {}
  list<State<T>*>* search(Searchable<T>* matrix) override {

    matrix->getInitialState()->setPathCost(matrix->getInitialState()->getCost());
    matrix->getInitialState()->setHeuristicCost(heuristicFunc(matrix->getInitialState(), matrix->getGoalState()));
    Searcher<T>::addToQueue(matrix->getInitialState());
    visited = new list<State<T>*>();

    while (Searcher<T>::queueSize() > 0) {
      State<T>* node = Searcher<T>::popQueueHeuristic();
      Searcher<T>::evaluatedNodes++;
      visited->push_back(node);

      if (matrix->isGoalState(node)) {
        list<State<T>*>* retVal = Searcher<T>::backTrace(matrix->getInitialState(), node);
        return retVal;
      }

      list<State<T>*> successors = matrix->getAllPossibleStates(node);

      for (State<T>* s: successors) {

        s->setHeuristicCost(heuristicFunc(s, matrix->getGoalState()));
        s->setPathCost(s->getCost() + node->getPathCost());

        if (!isVisited(s)) {
          if (!Searcher<T>::isQueueContains(s)) { // if s not in OPEN or CLOSE
            Searcher<T>::addToQueue(s);
          } else { // s in Open, check better path

            State<T>* sInQueue = Searcher<T>::getStateFromQueue(s);

            int oldCost = sInQueue->getPathCost(), newCost = s->getPathCost();

            if (newCost < oldCost) {
              //replace parent, pathCost, heuristicCost
              sInQueue->setParent(s->getParent());
              sInQueue->setPathCost(sInQueue->getCost() + s->getParent()->getPathCost());
            }
            Searcher<T>::addToQueue(sInQueue);
          }
        }
      }
    }
    return nullptr;
  }

  int heuristicFunc(State<T>* node, State<T>* goal) {
    int alpha = 1;
    int dx = abs(node->getState()->getRow() - goal->getState()->getRow());
    int dy = abs(node->getState()->getCol() - goal->getState()->getCol());
    return alpha * (dx + dy);
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

#endif //MILSTONE2__ASTAR_H_
