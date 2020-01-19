//
// Created by guy on 19/01/2020.
//

#ifndef MILSTONE2__OBJECTADAPTER_H_
#include "Solver.h"
#include "Searcher.h"
#define MILSTONE2__OBJECTADAPTER_H_

template<typename P, typename S, typename T>
class ObjectAdapter : public Solver<P, S> {

  Searcher<T> _searcher;

 public:
  ObjectAdapter(const Searcher<T>& searcher) : _searcher(searcher) {}

  S solve(P problem) override {
    Searchable<P> searchable;
    return _searcher.search(searchable);
  }
};

#endif //MILSTONE2__OBJECTADAPTER_H_
