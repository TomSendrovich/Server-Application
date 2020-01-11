#include "Solver.h"

//
// Created by tom5012 on 11/01/2020.
//
template<typename Solution, typename Problem>
Solver<Solution, Problem>::Solver(Solution solution, Problem problem):solution(solution), problem(problem) {}

template<>Solution* Solver<Solution, Problem>::solve(Problem &p) {}

