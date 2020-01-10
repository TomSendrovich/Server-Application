//
// Created by guy on 08/01/2020.
//

#include "Solution.h"

Solution::Solution(const string& solution) : _solution(solution) {}
Solution::~Solution() {}
const string& Solution::getSolution() const { return _solution; }
