//
// Created by tom5012 on 10/01/2020.
//

#ifndef MILSTONE2_FILECACHEMANAGER_H
#include "CacheManager.h"
#include <fstream>
#include "string"
#define MILSTONE2_FILECACHEMANAGER_H

class FileCacheManager : public CacheManager {

  ifstream inStream;
  ofstream outStream;
  bool isOutStreamOpen = false;

 public:
  FileCacheManager(int sizeNum) { CacheManager::size = sizeNum; }

  virtual bool isSolutionExist(string hashProblem) {

    //solution is at the cache memory
    if (CacheManager::cacheMap.find(hashProblem) != CacheManager::cacheMap.end()) {
      return true;
    } else {
      //solution is not in cache, maybe in disk (in a file at that case)
      string line;
      inStream.close();
      inStream.open(hashProblem + ".txt", ios::binary);
      return inStream.is_open();
    }
  }

  virtual string getSolution(string hashProblem) {

    //solution is at the cache memory
    if (CacheManager::cacheMap.find(hashProblem) != CacheManager::cacheMap.end()) {
      return CacheManager::cacheMap[hashProblem];
    } else {
      //solution is at the disk (in a file at that case)
      string line;
      inStream.close();
      inStream.open(hashProblem + ".txt", ios::in);
      if (!inStream.is_open()) {
        throw "Unable to open file";
      }
      getline(inStream, line);
      return line;
    }
  }

  virtual void saveSolution(string hashProblem, string solution) {
    outStream.close();
    outStream.open(hashProblem + ".txt", ios::out | ios::app);
    if (!outStream.is_open()) {
      throw "Unable to open file";
    }

    outStream << solution << endl;
    if (CacheManager::cacheMap.size() >= CacheManager::size) {
      CacheManager::cacheMap.erase(CacheManager::cacheMap.begin());
    }
    CacheManager::cacheMap[hashProblem] = solution;
  }

  virtual ~FileCacheManager() = default;
};
#endif //MILSTONE2_FILECACHEMANAGER_H
