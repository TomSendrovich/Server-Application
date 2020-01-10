//
// Created by tom5012 on 08/01/2020.
//

#ifndef MILSTONE2_SOLVER_H
#include "Problem.h"
#include "Solution.h"
#define MILSTONE2_SOLVER_H

class Solver {
 public:
  virtual Solution* solve(Problem& problem) = 0;
  virtual ~Solver() = default;
};

#endif //MILSTONE2_SOLVER_H
