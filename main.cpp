#include <iostream>
#include "CacheManager.h"
#include "FileCacheManager.cpp"

int main() {
  int size = 5;
  const char* problem = "3";
  string solution;
  FileCacheManager fileCacheManager(size);
  bool isExist = fileCacheManager.isSolutionExist(problem);
  if (isExist) {
    std::cout << "true" << endl;
    solution = fileCacheManager.getSolution(problem);
    std::cout << solution << endl;
  } else {
    std::cout << "false" << endl;
  }

  fileCacheManager.saveSolution("1", "tom sendrovich");
  fileCacheManager.saveSolution("2", "guy shoham");
  fileCacheManager.saveSolution("3", "ofir cohen");
  fileCacheManager.saveSolution("4", "hila bartov");
  fileCacheManager.saveSolution("5", "tzivka the king");
  fileCacheManager.saveSolution("6", "i dont mind");

  return 1;
}
