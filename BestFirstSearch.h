//
// Created by guy on 16/01/2020.
//

#ifndef MILSTONE2__BESTFIRSTSEARCH_H_
#include "Searcher.h"
#include "Cell.h"
#include <list>
#include <set>
using namespace std;
#define MILSTONE2__BESTFIRSTSEARCH_H_

template<typename T>
class BestFirstSearch : public Searcher<T> {

 public:
  Solution Search(Searchable<T> problem) override {
    addToOpenQueue(problem.getInitialState());
    unordered_set<State<T>> closed = new unordered_set<T>();

    while (Searcher<T>::openQueueSize() > 0) {
      State<T> node = Searcher<T>::popOpenQueue();
      closed.insert(node);
      if (problem.isGoalState(node)) {
        Solution s = backTrace(problem, closed);
        return s;
      }
      list<State<T>> successors = problem.getAllPossibleStates(node);

      for (State<T> s: successors) {
        if (closed.find(s) == closed.end() && !isOpenQueueContains(s)) {// if s not in OPEN or CLOSE
          addToOpenQueue(s); //parent of s was set in getAllPossibleStates
        } else {
          if (s.getParent().getCost() > node.getCost()) {//found a better path
            if (isOpenQueueContains(s)) {
              s.setCost(node.getCost() + s.getCost());
              removeFromOpenQueue(s);
              addToOpenQueue(s);
            } else {
              s.setCost(s.getParent().getCost() + s.getCost());
              addToOpenQueue(s);
            }
          }
        }
      }//end of foreach
    }
  }

  Solution backTrace(Searchable<T> problem, unordered_set<State<T>> set) {
    Solution solution;
    bool done = false;
    list<State<T>> trace = new ::list<State<T>>();
    State<T> currentState;

    //find the goal state
    for (State<T> it = set.begin(); it != set.end(); ++it) {
      if (problem.isGoalState(it)) {
        currentState = it;
        trace.push_back(it);
        break;
      }
    }

    while (!done) {
      for (State<T> it = set.begin(); it != set.end(); ++it) {

        if (currentState.getParent().equals(it)) {//found the parent of last state
          currentState = it;
          trace.push_back(it);

          if (problem.getInitialState().equals(it)) {
            done = true;
          }

          break;
        }
      }
    }

    //trace list is ready
    for (State<T> it = trace.begin(); it != trace.end(); ++it) {
      if (it == trace.begin()) {
        continue;
      }
      string direction = getDirection(it);
      int cost = it.getCost();
      string move = direction + " (" + to_string(cost) + ")";
      solution.addAction(move);
    }

    return solution;
  }

  ///return the correct direction depends of the pos of the state and his parent
  string getDirection(State<T> state) {
    int stateRow = state.getState().getPosition().getRow();
    int stateCol = state.getState().getPosition().getCol();
    int parentStateRow = state.getParent().getState().getPosition().getRow();
    int parentStateCol = state.getParent().getState().getPosition().getCol();

    if (stateRow - parentStateRow == 1 && stateCol - parentStateCol == 0) { return "Up"; }
    else if (stateRow - parentStateRow == -1 && stateCol - parentStateCol == 0) { return "Down"; }
    else if (stateRow - parentStateRow == 0 && stateCol - parentStateCol == 1) { return "Left"; }
    else if (stateRow - parentStateRow == 0 && stateCol - parentStateCol == -1) { return "Right"; }
    else return "Error";
  }
};

#endif //MILSTONE2__BESTFIRSTSEARCH_H_
