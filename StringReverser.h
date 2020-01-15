//
// Created by guy on 10/01/2020.
//

#ifndef MILSTONE2__STRINGREVERSER_H_
#include "Solver.h"
#define MILSTONE2__STRINGREVERSER_H_

template<typename P, typename S>
class StringReverser : public Solver<P, S> {

 public:
  StringReverser() = default;

  S& solve(P& problem) override {
    int n = problem.length();

    // Swap character starting from two corners
    for (int i = 0; i < n / 2; i++) {
      swap(problem[i], problem[n - i - 1]);
    }

    return problem;
  };
};

#endif //MILSTONE2__STRINGREVERSER_H_
