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
  StringReverser();

  string solve(string* problem) override;
};

#endif //MILSTONE2__STRINGREVERSER_H_
