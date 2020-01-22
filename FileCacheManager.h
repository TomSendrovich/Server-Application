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


class FileCacheManager : public CacheManager {

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

  bool isSolutionExistInDisk(string line, string problemHashName) {
    string tokenProblem;
    size_t pos;
    pos = line.find(DELIMITER);
    tokenProblem = line.substr(0, pos);

    return tokenProblem == problemHashName;
  }

 public:
  FileCacheManager(int sizeNum) { CacheManager::size = sizeNum; }

  virtual bool isSolutionExist(string problem) {

    string objectName = "string";
    string problemHashName = to_string(hash_str(problem.c_str()));

    //solution is at the cache memory
    if (CacheManager::cacheMap.find(problem) != CacheManager::cacheMap.end()) {
      return true;
    } else {
      //solution is not in cache, maybe in disk (in a file at that case)
      string line;
      inStream.close();
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

  virtual string getSolution(string problem) {
    string objectName = "string";
    string problemHashName = to_string(hash_str(problem.c_str()));

    //solution is at the cache memory
    if (CacheManager::cacheMap.find(problemHashName) != CacheManager::cacheMap.end()) {
      return CacheManager::cacheMap[problemHashName];
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
    }
  }

  virtual void saveSolution(string problem, string solution) {
    string objectName = "string";
    string problemHashName = to_string(hash_str(problem.c_str()));

    if (!isOutStreamOpen) {
      isOutStreamOpen = true;
      outStream.open(objectName + ".txt", ios::out | ios::app);
      if (!outStream.is_open()) {
        throw "Unable to open file";
      }
    }
    outStream << problemHashName + "," + solution << endl;
    if (CacheManager::cacheMap.size() >= CacheManager::size) {
      CacheManager::cacheMap.erase(CacheManager::cacheMap.begin());
    }
    CacheManager::cacheMap[problem] = solution;
  }

  virtual ~FileCacheManager() = default;
};
#endif //MILSTONE2_FILECACHEMANAGER_H
