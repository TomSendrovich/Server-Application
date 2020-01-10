//
// Created by guy on 08/01/2020.
//

#ifndef MILSTONE2__PROBLEM_H_
#include <string>
using namespace std;
#define MILSTONE2__PROBLEM_H_

class Problem {
  string _problem;

 public:
  Problem(const string& problem);
  const string& getProblem() const;
  virtual ~Problem();
};

#endif //MILSTONE2__PROBLEM_H_
