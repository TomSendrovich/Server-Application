//
// Created by guy on 13/01/2020.
//

#ifndef MILSTONE2__SEARCHER_H_
#include "Searchable.h"
#include "Solution.h"
#define MILSTONE2__SEARCHER_H_
template<typename T>
class Searcher {

  int evaluatedNodes;
  Searchable<T> problem;

 public:
  virtual Solution Search(Searchable<T> problem) = 0;
  virtual int getNumberOfNodesEvaluated() = 0;
};

#endif //MILSTONE2__SEARCHER_H_
