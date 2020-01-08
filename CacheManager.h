//
// Created by guy on 08/01/2020.
//

#ifndef MILSTONE2__CACHEMANAGER_H_
using namespace std;

#include "Solution.h"

#define MILSTONE2__CACHEMANAGER_H_

#include <unordered_map>

class CacheManager {
protected:
    unordered_map<const char *, const char *> cacheMap;
    int size;

public:
    virtual bool isSolutionExist(const char* solution) = 0;
    //should be: virtual Solution getSolution()
    virtual string getSolution(const char* problem) = 0;

    virtual void saveSolution(const char* solution) = 0;

    virtual ~CacheManager() = default;
};

#endif //MILSTONE2__CACHEMANAGER_H_
