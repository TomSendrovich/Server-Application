//
// Created by guy on 08/01/2020.
//

#ifndef MILSTONE2__MYTESTCLIENTHANDLER_H_

#include <ostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <sstream>
#include <thread>
#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"

using namespace std;
#define MILSTONE2__MYTESTCLIENTHANDLER_H_

template<typename P, typename S>
class MyTestClientHandler : public ClientHandler {

  Solver<P, S>* _solver;
  CacheManager* _cm;
  bool isEnd, needToRead;

  bool sendMsg(int out, const char* msg) {
    int is_sent = send(out, msg, strlen(msg), 0);
    return is_sent != -1;
  }

 public:
  MyTestClientHandler(Solver<P, S>* solver, CacheManager* cm) {
    _solver = solver;
    _cm = cm;
  }

  ~MyTestClientHandler() override {
    delete _solver;
    delete _cm;
  }

  void handleClient(int in) override {
    isEnd = false;
    char buffer[1024] = {0};
    char* ptrBuffer = buffer;
    while (!isEnd) {
      int valRead = read(in, buffer, 1024);
      if (valRead == 0 || valRead == -1) {
        throw "ERROR: message from client did not receive";
      }
      string allLines = ptrBuffer;
      string oneLine = allLines;
      int pos = oneLine.find('\n');
      oneLine.erase(pos, oneLine.length() - pos);
      allLines.erase(0, pos + 1);
      if (oneLine != "end") { //there is a line to read
        string problem = oneLine;

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
        problem.clear();
      } else {
        //client wants to end communication
        isEnd = true;
      }

    }//end of while loop
  }

};//end of class

#endif //MILSTONE2__MYTESTCLIENTHANDLER_H_
