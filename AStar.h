//
// Created by guy on 24/01/2020.
//

#ifndef MILSTONE2__ASTAR_H_
#include "Searcher.h"
#include "Cell.h"
#include <list>
#include <set>
#include <iostream>
#define MILSTONE2__ASTAR_H_

template<typename T>
class AStar : public Searcher<T> {

  list<State<T>*>* visited;

 public:
  AStar() { Searcher<T>::evaluatedNodes = 0; }
  list<State<T>*>* search(Searchable<T>* problem) override {

    Searcher<T>::addToPriorityQueue(problem->getInitialState());
    visited = new list<State<T>*>();

    while (Searcher<T>::priorityQueueSize() > 0) {
      State<T>* node = Searcher<T>::popPriorityQueueHeuristic();
      Searcher<T>::evaluatedNodes++;
      visited->push_back(node);

      if (problem->isGoalState(node)) {
        list<State<T>*>* retVal = Searcher<T>::backTrace(problem->getInitialState(), node);
        return retVal;
      }

      cout << "nodes: " << Searcher<T>::getNumOfEvaluatedNodes() << ", open: " << Searcher<T>::priorityQueueSize()
           << ", close: " << visited->size() << endl;


      /*if (Searcher<T>::getNumOfEvaluatedNodes() == 500) {
        cout << "HI" << endl;
        cout <<  Searcher<T>::getNumOfEvaluatedNodes() << endl;
      }*/

      list<State<T>*> successors = problem->getAllPossibleStates(node);

      for (State<T>* s: successors) {

        s->setHeuristicCost(heuristicFunc(s, problem->getGoalState()));
        s->setPathCost(s->getCost() + node->getPathCost());

        if (!isVisited(s) && !Searcher<T>::isPriorityQueueContains(s)) {// if s not in OPEN or CLOSE
          Searcher<T>::addToPriorityQueue(s); ///parent of s was set in getAllPossibleStates
        } else {
          /*if (Searcher<T>::isPriorityQueueContains(s)) {
            if(s->getPathCost()+s->getCost()<)
          }*/
        }
      }//end of foreach
    }

    /*visited = new list<State<T>*>();

    //pathCost = cost for initial state
    problem->getInitialState()->setPathCost(problem->getInitialState()->getCost());

    //mark initial state visited
    visited->push_front(problem->getInitialState());

    //push initial state to queue
    Searcher<T>::addToQueue(problem->getInitialState());

    //while queue is not empty
    while (Searcher<T>::queueSize() > 0) {
      State<T>* node = Searcher<T>::popQueue();
      visited->push_back(node);
      Searcher<T>::evaluatedNodes++;

      *//*if (Searcher<T>::getNumOfEvaluatedNodes() == 116) {
        cout << "HI" << endl;
        cout <<  Searcher<T>::getNumOfEvaluatedNodes() << endl;
      }

      if (node == nullptr) {
        cout << "null node" << endl;
        cout <<  Searcher<T>::getNumOfEvaluatedNodes() << endl;
      }*//*

      //case for initial state that has no parent
      if (node->getParent() != nullptr) {
        node->setPathCost(node->getParent()->getPathCost() + node->getCost());
      }

      //if node is goal state, check backtrace
      if (problem->isGoalState(node)) {
        list<State<T>*>* retVal = Searcher<T>::backTrace(problem->getInitialState(), node);
        return retVal;
      }

      //get all successors
      list<State<T>*> successors = problem->getAllPossibleStates(node);

      State<T>* s = findBestSuccessor(successors, problem->getGoalState());
      Searcher<T>::addToQueue(s);

    }*/
  }

  /*State<T>* calcHeuristicCost(list<State<T>*> successors, State<T>* goal) {
    int g, f, h;
    int minF = 99999;
    State<T>* minFState = nullptr;

    for (State<T>* s: successors) {
      if (!isVisited(s)) {

        if (s->getParent() != nullptr) {
          g = s->getCost() + s->getParent()->getPathCost();
        } else {
          g = 0;
          cout << "no parent: " << s->getState()->getRow() << "," << s->getState()->getCol() << endl;
        }
        h = heuristicFunc(s, goal);
        f = g + h;

        if (f < minF) {
          minF = f;
          minFState = s;
        }
      }
    }

    return minFState;

  }*/

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
