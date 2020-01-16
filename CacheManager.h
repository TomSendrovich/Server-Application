//
// Created by guy on 08/01/2020.
//

#ifndef MILSTONE2__CACHEMANAGER_H_
#include <list>
#include <unordered_map>
using namespace std;
#define MILSTONE2__CACHEMANAGER_H_

template<typename P, typename S>

class CacheManager {
 protected:
  unordered_map<P, S> cacheMap;
  int size;

 public:
  virtual bool isSolutionExist(P& problem) = 0;
  //should be: virtual Solution getSolution()
  virtual S getSolution(P& problem) = 0;

  virtual void saveSolution(P& problem, S& solution) = 0;

  virtual ~CacheManager() = default;
};

#endif //MILSTONE2__CACHEMANAGER_H_
