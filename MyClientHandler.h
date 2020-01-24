//
// Created by tom5012 on 19/01/2020.
//

#ifndef MILSTONE2__MYCLIENTHANDLER_H_
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <unordered_map>
#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include "MatrixProblem.h"
using namespace std;

#define MILSTONE2__MYCLIENTHANDLER_H_
template<typename P, typename S>

class MyClientHandler : public ClientHandler {
  Solver<P, S>* _solver;
  CacheManager* _cm;
  vector<vector<string>> matrix;
  bool isEnd;
  hash<string> hasher;
  size_t hashName;

  bool sendMsg(int out, const char* msg) {
    int is_sent = send(out, msg, strlen(msg), 0);
    return is_sent != -1;
  }

 public:
  MyClientHandler(Solver<P, S>* solver, CacheManager* cm) {
    _solver = solver;
    _cm = cm;
  }
  ~MyClientHandler() override {
    delete _solver;
    delete _cm;
  }
  void handleClient(int in) override {
    matrix.clear();
    isEnd = false;
    bool inCell = false, isValRead = false;
    vector<string> completeRow;
    Cell* initCell = nullptr, * goalCell = nullptr;
    int row = -1, col = 0, pos, value, matrixSize = 0;
    char buffer[1024] = {0};
    char* ptrBuffer = buffer;
    string singleState, allLines;
    while (!isValRead) {
      int valRead = read(in, buffer, 1);
      if (valRead == 0 || valRead == -1) {
        isValRead = true;
      } else {
        allLines += ptrBuffer;

        if (allLines.find("end", 0) != string::npos) {
          break;
        }
      }
    }
    hashName = hasher(allLines);
    while (!isEnd) {
      pos = allLines.find('\n');
      string oneLine = allLines;
      if (oneLine != "end") {
        oneLine.erase(pos, oneLine.length() - pos);
        allLines.erase(0, pos + 1);
        string problem = oneLine;
        while (!problem.empty()) {
          pos = problem.find(',');
          if (pos != -1) {
            singleState = problem.erase(pos, problem.length() - pos);
            oneLine.erase(0, pos + 1);
          } else {
            singleState = oneLine;
            oneLine.erase(0, oneLine.length());
          }
          completeRow.push_back(singleState);
          problem = oneLine;
        }
        if (completeRow.size() == 2 && !inCell) {
          row = atoi(completeRow.begin()->c_str());
          col = atoi(completeRow.rbegin()->c_str());
          pair<int, int> p = make_pair(row, col);
          value = atoi(matrix[row][col].c_str());
          initCell = new Cell(p, value);
          inCell = true;
        } else if (completeRow.size() == 2 && inCell) {
          row = atoi(completeRow.begin()->c_str());
          col = atoi(completeRow.rbegin()->c_str());
          value = atoi(matrix[row][col].c_str());
          pair<int, int> p1 = make_pair(row, col);
          goalCell = new Cell(p1, value);
          inCell = true;
        } else {
          matrix.push_back(completeRow);
          matrixSize++;
          //cout << "completeRow" << endl;
        }
        completeRow.clear();
      } else {
        ///client wants to end communication
        auto* problem = new MatrixProblem(matrix, initCell, goalCell, matrixSize);
        string hashProblem = to_string(hashName);
        if (_cm->isSolutionExist(hashProblem)) {
          string solutionExist = _cm->getSolution(hashProblem);
          if (!sendMsg(in, solutionExist.c_str())) {
            cerr << "Error sending message: " << solutionExist << endl;
          }
        } else {
          //solutionNotExist dont exist in cm, we solve the problem and save it at cm
          string solutionNotExist = _solver->solve(problem);
          _cm->saveSolution(hashProblem, solutionNotExist);
          if (!sendMsg(in, solutionNotExist.c_str())) {
            cerr << "Error sending message: " << solutionNotExist << endl;
          }
        }
        isEnd = true;
      }
    }
  }
  ClientHandler* copy() {
    ClientHandler* newClientHandler = new MyClientHandler(_solver, _cm);
    return newClientHandler;
  }
};

#endif //MILSTONE2__MYCLIENTHANDLER_H_
