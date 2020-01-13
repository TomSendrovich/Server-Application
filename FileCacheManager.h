//
// Created by tom5012 on 10/01/2020.
//

#ifndef MILSTONE2_FILECACHEMANAGER_H
#include "CacheManager.h"
#include <fstream>
#include "string"
#define MILSTONE2_FILECACHEMANAGER_H

template<class P, class S>
class FileCacheManager : public CacheManager<P, S> {

  ifstream inStream;
  ofstream outStream;
  bool isOutStreamOpen = false;

 public:
  FileCacheManager<P, S>(int sizeNum) { CacheManager<P, S>::size = sizeNum; }

  bool isSolutionExist(P& problem) override {
    /*//solution is at the cache memory
    if (CacheManager<P, S>::cacheMap.find(problem) != CacheManager<P, S>::cacheMap.end()) { return true; }
    else {
      //solution is at the disk (in a file at that case)
      string line;
      inStream.open("disk.txt", ios::in);
      if (!inStream.is_open()) { throw "Unable to open file"; }
      while (getline(inStream, line)) {
        string delimiter = ",";
        if (isSolutionExistInDisk(line, problem, delimiter)) { return true; }
      }
    }*/
    return false;
  }

  S& getSolution(P& problem) override {
    //solution is at the cache memory
    if (CacheManager<P, S>::cacheMap.find(problem) != CacheManager<P, S>::cacheMap.end()) {
      return CacheManager<P, S>::cacheMap[problem];
    } else {
      //solution is at the disk (in a file at that case)
      string line;
      inStream.close();
      inStream.open("disk.txt", ios::in);
      if (!inStream.is_open()) { throw "Unable to open file"; }
      while (getline(inStream, line)) {
        string delimiter = ",";
        if (isSolutionExistInDisk(line, problem, delimiter)) {
          size_t pos = line.find(delimiter) != std::string::npos;
          line.erase(0, pos + delimiter.length());
          return line;
        }
      }

    }
  }

  void saveSolution(P& problem, S& solution) override {
   /* if (!isOutStreamOpen) {
      isOutStreamOpen = true;
      outStream.open("disk.txt", ios::out | ios::app);
      if (!outStream.is_open()) {
        throw "Unable to open file";
      }
    }
    outStream << problem << ", " << solution << endl;
    if (CacheManager<P, S>::cacheList.size() >= CacheManager<P, S>::size) {
      pair<const char*, const char*> lastElement = CacheManager<P, S>::cacheList.back();
      CacheManager<P, S>::cacheList.pop_back();
      CacheManager<P, S>::cacheMap.erase(lastElement.first);
    }
    CacheManager<P, S>::cacheList.push_front(make_pair(problem, solution));
    CacheManager<P, S>::cacheMap[problem] = solution;*/
  }

  ~FileCacheManager() override = default;

  bool isSolutionExistInDisk(string line, P& problem, string delimiter) {
    string tokenProblem;
    size_t pos;
    pos = line.find(delimiter) != std::string::npos;
    tokenProblem = line.substr(0, pos);

    return tokenProblem == problem;
  }
};
#endif //MILSTONE2_FILECACHEMANAGER_H
