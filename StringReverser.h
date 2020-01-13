//
// Created by guy on 10/01/2020.
//

#ifndef MILSTONE2__STRINGREVERSER_H_
#include <algorithm>
#include <sstream>
#include "Solver.h"
#define MILSTONE2__STRINGREVERSER_H_

template<class P, class S>
class StringReverser : public Solver<P, S> {

  string problemToString(P& problem) {
    return to_string(problem);
  };

  S& solvedStringToSolution(string solution) {
    istringstream ss(solution);
    S* retVal = nullptr;
    ss >> retVal;
    return retVal;
  };

 public:
  StringReverser() {}
  S& solve(P& problem) override {
    /*string problemStr = problemToString(problem);
    int length = problemStr.length();

    // Swap character starting from two corners
    for (int i = 0; i < length / 2; i++)
      swap(problemStr[i], problemStr[length - i - 1]);

    S* solution = solvedStringToSolution(problemStr);
    return solution;*/
  };
};

#endif //MILSTONE2__STRINGREVERSER_H_
