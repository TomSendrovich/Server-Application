#include <iostream>
#include "CacheManager.h"
#include "FileCacheManager.cpp"

int main() {
    int size = 5;
    const char *problem = "3";
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

    //fileCacheManager.saveSolution(solution);


    return 1;
}
