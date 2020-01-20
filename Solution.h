//
// Created by guy on 18/01/2020.
//

#ifndef MILSTONE2__SOLUTION_H_
#include <string>
using namespace std;
#define MILSTONE2__SOLUTION_H_

class Solution {
  string _solution = "";

 public:
  Solution() = default;
  void addAction(const string& act) {
    if (_solution.empty()) {
      _solution += act;
    } else {
      _solution += ", " + act;
    }
  }
  string to_string() {
    return _solution;
  }
};

#endif //MILSTONE2__SOLUTION_H_
