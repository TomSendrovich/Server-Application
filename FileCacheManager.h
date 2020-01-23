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

  virtual bool isSolutionExist(string hashProblem) {

    //solution is at the cache memory
    if (CacheManager::cacheMap.find(hashProblem) != CacheManager::cacheMap.end()) {
      return true;
    } else {
      //solution is not in cache, maybe in disk (in a file at that case)
      string line;
      inStream.close();
      inStream.open(hashProblem + ".txt", ios::binary);
      if (!inStream.is_open()) {
        return false;
      }
      while (getline(inStream, line)) {
        if (isSolutionExistInDisk(line, hashProblem)) {
          return true;
        }
      }
    }
    return false;
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
      while (getline(inStream, line)) {
        if (isSolutionExistInDisk(line, hashProblem)) {
          size_t pos = line.find(DELIMITER);
          line.erase(0, pos + DELIMITER_LENGTH);
          return line;
        }
      }
    }
  }

  virtual void saveSolution(string hashProblem, string solution) {
    if (!isOutStreamOpen) {
      isOutStreamOpen = true;
      outStream.open(hashProblem + ".txt", ios::out | ios::app);
      if (!outStream.is_open()) {
        throw "Unable to open file";
      }
    }
    outStream << hashProblem + "," + solution << endl;
    if (CacheManager::cacheMap.size() >= CacheManager::size) {
      CacheManager::cacheMap.erase(CacheManager::cacheMap.begin());
    }
    CacheManager::cacheMap[hashProblem] = solution;
  }

  virtual ~FileCacheManager() = default;
};
#endif //MILSTONE2_FILECACHEMANAGER_H
