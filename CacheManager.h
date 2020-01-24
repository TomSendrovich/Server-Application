//
// Created by guy on 08/01/2020.
//

#ifndef MILSTONE2__CACHEMANAGER_H_
#include <list>
#include <unordered_map>
using namespace std;
#define MILSTONE2__CACHEMANAGER_H_

class CacheManager {
 protected:
  unordered_map<string, string> cacheMap;
  int size;

 public:
  virtual bool isSolutionExist(string problem) = 0;
  //should be: virtual Solution getSolution()
  virtual string getSolution(string problem) = 0;

  virtual void saveSolution(string problem, string solution) = 0;

  virtual ~CacheManager() = default;
};

#endif //MILSTONE2__CACHEMANAGER_H_
