//
// Created by guy on 10/01/2020.
//

#ifndef MILSTONE2__STRINGREVERSER_H_
#include "Solver.h"
#include <string>
using namespace std;
#define MILSTONE2__STRINGREVERSER_H_

class StringReverser : public Solver<string, string> {

 public:
  StringReverser() ;

  string solve(string problem) override {
    string retVal = problem;
    int n = problem.length();

    // Swap character starting from two corners
    for (int i = 0; i < n / 2; i++) {
      swap(retVal[i], retVal[n - i - 1]);
    }

    return retVal;
  };
};

#endif //MILSTONE2__STRINGREVERSER_H_
