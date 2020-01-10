//
// Created by tom5012 on 10/01/2020.
//

#ifndef MILSTONE2_FILECACHEMANAGER_H
#include "CacheManager.h"
#define MILSTONE2_FILECACHEMANAGER_H

class FileCacheManager: public CacheManager{
    ifstream inStream;
    ofstream outStream;
    bool isOutStreamOpen = false;
public:
    FileCacheManager(int sizeNum);

    bool isSolutionExist(const char *problem) override;

    string getSolution(const char *problem) override;

    void saveSolution(const char *problem, const char *solution) override;

    // ~FileCacheManager() override = default;

    bool isSolutionExistInDisk(string line, const char* problem, string delimeter);
};
#endif //MILSTONE2_FILECACHEMANAGER_H
