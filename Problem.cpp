//
// Created by guy on 08/01/2020.
//

#include "Problem.h"

Problem::Problem(const string& problem) : _problem(problem) {}
Problem::~Problem() {}
const string& Problem::getProblem() const { return _problem; }
