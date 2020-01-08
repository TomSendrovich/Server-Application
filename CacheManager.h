//
// Created by guy on 08/01/2020.
//

#ifndef MILSTONE2__CACHEMANAGER_H_
#define MILSTONE2__CACHEMANAGER_H_

class CacheManager {

 public:
  virtual bool isSolutionExist() = 0;
  virtual Solution getSolution() = 0;
  virtual void saveSolution() = 0;
  virtual ~CacheManager() = default;
};

#endif //MILSTONE2__CACHEMANAGER_H_
