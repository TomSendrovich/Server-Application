//
// Created by tom5012 on 08/01/2020.
//

#include "FileCacheManager.h"

FileCacheManager::FileCacheManager(int sizeNum) {
  size = sizeNum;
}

bool FileCacheManager::isSolutionExist(const char* problem) {
  //solution is at the cache memory
  if (cacheMap[problem] != nullptr) {
    return true;
  } else {
    //soultion is at the disk (in a file at that case)
    string line;
    inStream.open("disk.txt", ios::in);
    if (!inStream.is_open()) {
      throw "Unable to open file";
    }
    while (getline(inStream, line)) {
      string delimeter = ",";
      if (isSolutionExistInDisk(line, problem, delimeter)) {
        return true;
      }
    }
  }
  return false;
}

string FileCacheManager::getSolution(const char* problem) {
  //solution is at the cache memory
  if (cacheMap[problem] != nullptr) {
    return cacheMap[problem];
  } else {
    //soultion is at the disk (in a file at that case)
    string line;
    inStream.close();
    inStream.open("disk.txt", ios::in);
    if (!inStream.is_open()) {
      throw "Unable to open file";
    }
    while (getline(inStream, line)) {
      string delimeter = ",";
      if (isSolutionExistInDisk(line, problem, delimeter)) {
        size_t pos = line.find(delimeter) != std::string::npos;
        line.erase(0, pos + delimeter.length());
        return line;
      }
    }
  }

}

void FileCacheManager::saveSolution(const char* problem, const char* solution) {
  if (!isOutStreamOpen) {
    isOutStreamOpen = true;
    outStream.open("disk.txt", ios::out | ios::app);
    if (!outStream.is_open()) {
      throw "Unable to open file";
    }
  }
  outStream << problem << ", " << solution << endl;
  if (cacheList.size() >= size) {
    pair<const char*, const char*> lastElement = cacheList.back();
    cacheList.pop_back();
    cacheMap.erase(lastElement.first);
  }
  cacheList.push_front(make_pair(problem, solution));
  cacheMap[problem] = solution;
}

bool FileCacheManager::isSolutionExistInDisk(string line, const char* problem, string delimiter) {

  string tokenProblem;
  size_t pos;
  pos = line.find(delimiter) != std::string::npos;
  tokenProblem = line.substr(0, pos);

  return tokenProblem == problem;
}
