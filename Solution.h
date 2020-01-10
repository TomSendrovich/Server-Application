//
// Created by guy on 08/01/2020.
//

#ifndef MILSTONE2__SOLUTION_H_
#include <string>
using namespace std;
#define MILSTONE2__SOLUTION_H_

class Solution {
  string _solution;

 public:
  Solution(const string& solution);
  const string& getSolution() const;
  virtual ~Solution();
};

#endif //MILSTONE2__SOLUTION_H_
