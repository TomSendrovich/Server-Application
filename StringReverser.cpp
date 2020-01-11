//
// Created by guy on 10/01/2020.
//

#include <algorithm>
#include "StringReverser.h"
Solution* StringReverser::solve(Problem& problem) {

  string str = problem.getProblem();
  int length = str.length();

  // Swap character starting from two corners
  for (int i = 0; i < length / 2; i++)
    swap(str[i], str[length - i - 1]);

  Solution* solution = new Solution(str);
  return solution;
}
