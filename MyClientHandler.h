//
// Created by tom5012 on 19/01/2020.
//

#ifndef MILSTONE2__MYCLIENTHANDLER_H_
#include <ostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <sstream>
#include <thread>
#include <vector>
#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include "State.h"
#include "Cell.h"
#include "MatrixProblem.h"
using namespace std;

#define MILSTONE2__MYCLIENTHANDLER_H_
template<typename P, typename S, typename T>

class MyClientHandler : public ClientHandler {
  Solver<P, S>* _solver;
  CacheManager<P, S>* _cm;
  vector<vector<State<T>>> matrix;
  bool isEnd, needToRead;

  bool sendMsg(int out, const char* msg) {
    int is_sent = send(out, msg, strlen(msg), 0);
    return is_sent != -1;
  }

 public:
  MyClientHandler(Solver<P, S>* solver, CacheManager<P, S>* cm) {
    _solver = solver;
    _cm = cm;
  }

  ~MyClientHandler() override {
    delete _solver;
    delete _cm;
  }

  void handleClient(int in) override {
    isEnd = false;
    bool inCell = false;
    Cell* initCell, * goalCell;
    int row = -1, col = 0;
    char buffer[1024] = {0};
    char* ptrBuffer = buffer;
    while (!isEnd) {
      int valRead = read(in, buffer, 1024);
      if (valRead == 0 || valRead == -1) {
        throw "ERROR: message from client did not receive";
      }
      string oneLine = ptrBuffer;
      oneLine.erase(oneLine.length() - 1, 1);//erase \n
      if (oneLine != "end") {
        row++;
        string problem = oneLine;
        while (problem != "") {
          int pos = problem.find(',');
          if (problem.find(',', pos + 1) != -1) {
            string singleState = problem.erase(0, problem.length() - pos);
            Cell* cell = new Cell(new Position(row, col), atoi(singleState.c_str()));
            State<T> state = new State<T>(cell);
            matrix[row][col] = state;
            col++;
            oneLine.erase(0, pos + 1);
            problem = oneLine;
          } else {
            if (!inCell) {
              row = atoi(problem.erase(pos, problem.length() - pos).c_str());
              col = atoi(oneLine.erase(0, pos + 1).c_str());
              initCell = matrix[row][col];
              inCell = true;
            } else {
              row = atoi(problem.erase(pos, problem.length() - pos).c_str());
              col = atoi(oneLine.erase(0, pos + 1).c_str());
              goalCell = matrix[row][col];
            }
          }

        }
      } else {
        //client wants to end communication
        MatrixProblem<T> problem = new MatrixProblem<T>(matrix, initCell, goalCell);
        if (_cm->isSolutionExist(problem)) {
          //solutionExist exist in cm, we return in to the client
          S solutionExist = _cm->getSolution(problem);
          if (!sendMsg(in, solutionExist.c_str())) {
            cout << "Error sending message: " << solutionExist << endl;
          }
        } else {
          //solutionNotExist dont exist in cm, we solve the problem and save it at cm
          S solutionNotExist = _solver->solve(problem);
          _cm->saveSolution(problem, solutionNotExist);
          if (!sendMsg(in, solutionNotExist.c_str())) {
            cout << "Error sending message: " << solutionNotExist << endl;
          }
        }
        cout << "end line" << endl;
        isEnd = true;
      }
    }
  }

};

#endif //MILSTONE2__MYCLIENTHANDLER_H_
