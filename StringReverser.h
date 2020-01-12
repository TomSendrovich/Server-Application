//
// Created by guy on 10/01/2020.
//

#ifndef MILSTONE2__STRINGREVERSER_H_
#include <algorithm>
#include "Solver.h"
#define MILSTONE2__STRINGREVERSER_H_

template<class P, class S>
class StringReverser : public Solver<P, S> {

 public:
  //todo: implement solve
  S& solve(P& problem) override {
    /*string str = problem.getProblem();
    int length = str.length();

    // Swap character starting from two corners
    for (int i = 0; i < length / 2; i++)
      swap(str[i], str[length - i - 1]);

    S* solution = new S(str);
    return solution;
  }*/
  };
};

#endif //MILSTONE2__STRINGREVERSER_H_
