//
// Created by tom5012 on 10/01/2020.
//

#ifndef MILSTONE2_FILECACHEMANAGER_H
#include "CacheManager.h"
#include <fstream>
#include "string"
#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */
#define DELIMITER ","
#define DELIMITER_LENGTH 1

#define MILSTONE2_FILECACHEMANAGER_H

template<typename P, typename S>
class FileCacheManager : public CacheManager<P, S> {

  ifstream inStream;
  ofstream outStream;
  bool isOutStreamOpen = false;

  unsigned hash_str(const char* s) {
    unsigned h = FIRSTH;
    while (*s) {
      h = (h * A) ^ (s[0] * B);
      s++;
    }
    return h; // or return h % C;
  }

  //todo: test this function
  bool isSolutionExistInDisk(string line, string problemHashName) {
    string tokenProblem;
    size_t pos;
    pos = line.find(DELIMITER);
    tokenProblem = line.substr(0, pos);

    return tokenProblem == problemHashName;
  }

 public:
  FileCacheManager<P, S>(int sizeNum) { CacheManager<P, S>::size = sizeNum; }

  bool isSolutionExist(P& problem) override {

    string objectName = "string";
    string problemHashName = to_string(hash_str(problem.c_str()));

    //solution is at the cache memory
    if (CacheManager<P, S>::cacheMap.find(problem) != CacheManager<P, S>::cacheMap.end()) {
      return true;
    } else {
      //solution is not in cache, maybe in disk (in a file at that case)
      string line;
      inStream.open(objectName + ".txt", ios::binary);
      if (!inStream.is_open()) {
        throw "Unable to open file";
      }
      while (getline(inStream, line)) {
        if (isSolutionExistInDisk(line, problemHashName)) {
          return true;
        }
      }
    }
    return false;
  }

  S& getSolution(P& problem) override {
    S ans = "abc";
    S ret = ans;
    return ret;

    /*string objectName = "string";
    string problemHashName = to_string(hash_str(problem.c_str()));

    //solution is at the cache memory
    if (CacheManager<P, S>::cacheMap.find(problemHashName) != CacheManager<P, S>::cacheMap.end()) {
      return CacheManager<P, S>::cacheMap[problemHashName];
    } else {
      //solution is at the disk (in a file at that case)
      string line;
      inStream.close();
      inStream.open(objectName + ".txt", ios::in);
      if (!inStream.is_open()) {
        throw "Unable to open file";
      }
      while (getline(inStream, line)) {
        if (isSolutionExistInDisk(line, problemHashName)) {
          size_t pos = line.find(DELIMITER);
          line.erase(0, pos + DELIMITER_LENGTH);
          return line;
        }
      }
    }*/
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
};
#endif //MILSTONE2_FILECACHEMANAGER_H
