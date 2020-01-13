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
  StringReverser() = default;

  S& solve(P& problem) override {
    return problem;
  };
};

#endif //MILSTONE2__STRINGREVERSER_H_
