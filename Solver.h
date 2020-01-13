//
// Created by tom5012 on 08/01/2020.
//

#ifndef MILSTONE2_SOLVER_H
#define MILSTONE2_SOLVER_H

template<class P, class S>

class Solver {
 public:
  virtual S& solve(P& problem) = 0;
  virtual ~Solver() = default;
};

#endif //MILSTONE2_SOLVER_H
