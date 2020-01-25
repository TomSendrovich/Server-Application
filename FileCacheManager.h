//
// Created by tom5012 on 10/01/2020.
//

#ifndef MILSTONE2_FILECACHEMANAGER_H
#include "CacheManager.h"
#include <fstream>
#include <iostream>
#include <mutex>
#define MILSTONE2_FILECACHEMANAGER_H

class FileCacheManager : public CacheManager {

  ifstream inStream;
  ofstream outStream;
  mutex file_lock, cache_lock;

 public:
  FileCacheManager(int sizeNum) { CacheManager::size = sizeNum; }

  virtual bool isSolutionExist(string hashProblem) {
    cout << "isSolutionExist" << endl;
    //solution is at the cache memory
    cache_lock.lock();
    if (CacheManager::cacheMap.find(hashProblem) != CacheManager::cacheMap.end()) {
      cache_lock.unlock();
      return true;
    } else {
      cache_lock.unlock();
      //solution is not in cache, maybe in disk (in a file at that case)
      string line;
      file_lock.lock();
      inStream.open(hashProblem + ".txt", ios::binary);
      bool isOpen = inStream.is_open();
      if (isOpen) {
        inStream.close();
      }
      file_lock.unlock();
      cout << "isSolutionExistEnd" << endl;
      return isOpen;
    }
  }

  virtual string getSolution(string hashProblem) {
    file_lock.lock();
    cout << "getSolution" << endl;
    //solution is at the cache memory
    if (CacheManager::cacheMap.find(hashProblem) != CacheManager::cacheMap.end()) {
      file_lock.unlock();
      return CacheManager::cacheMap[hashProblem];
    } else {
      //solution is at the disk (in a file at that case)
      string line;
      inStream.open(hashProblem + ".txt", ios::in);
      if (!inStream.is_open()) {
        file_lock.unlock();
        throw "Unable to open file";
      }
      getline(inStream, line);
      if (CacheManager::cacheMap.size() >= CacheManager::size) {
        CacheManager::cacheMap.erase(CacheManager::cacheMap.begin());
      }
      cache_lock.lock();
      CacheManager::cacheMap[hashProblem] = line;
      cache_lock.unlock();
      inStream.close();
      file_lock.unlock();
      return line;
    }
  }

  virtual void saveSolution(string hashProblem, string solution) {
    file_lock.lock();
    cout << "saveSolution" << endl;
    outStream.open(hashProblem + ".txt", ios::out | ios::app);
    if (!outStream.is_open()) {
      file_lock.unlock();
      throw "Unable to open file";
    }

    outStream << solution << endl;
    cache_lock.lock();
    if (CacheManager::cacheMap.size() >= CacheManager::size) {
      CacheManager::cacheMap.erase(CacheManager::cacheMap.begin());
    }
    CacheManager::cacheMap[hashProblem] = solution;
    cache_lock.unlock();
    outStream.close();
    file_lock.unlock();
  }

  virtual ~FileCacheManager() = default;
};
#endif //MILSTONE2_FILECACHEMANAGER_H
