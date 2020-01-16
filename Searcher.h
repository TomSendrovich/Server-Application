//
// Created by guy on 13/01/2020.
//

#ifndef MILSTONE2__SEARCHER_H_
#include "Searchable.h"
#define MILSTONE2__SEARCHER_H_
template<typename T, typename S>
class Searcher {

  int evaluatedNodes;
  Searchable<T> problem;

 public:
  virtual S Search(Searchable<T> problem) = 0;
};

#endif //MILSTONE2__SEARCHER_H_
