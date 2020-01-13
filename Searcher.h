//
// Created by guy on 13/01/2020.
//

#ifndef MILSTONE2__SEARCHER_H_
#include "Searchable.h"
#define MILSTONE2__SEARCHER_H_
template<class T, class S>
class Searcher {
  S& Search(Searchable<T> searchable) = 0;
};

#endif //MILSTONE2__SEARCHER_H_
