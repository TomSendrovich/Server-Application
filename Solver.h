//
// Created by tom5012 on 08/01/2020.
//

#ifndef MILSTONE2_SOLVER_H
#define MILSTONE2_SOLVER_H

template<class P, class S>

class Solver {
  P _problem;
  S _solution;
 public:
  Solver<P, S>(P problem, S solution) {
    _problem = problem;
    _solution = solution;
  }

  virtual S* solve(P& problem) = 0;
  virtual ~Solver() = default;
};

#endif //MILSTONE2_SOLVER_H
