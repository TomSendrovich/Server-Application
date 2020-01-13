//
// Created by guy on 08/01/2020.
//

#ifndef MILSTONE2__MYTESTCLIENTHANDLER_H_

#include <ostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <sstream>
#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"

#define MILSTONE2__MYTESTCLIENTHANDLER_H_

template<class P, class S>
class MyTestClientHandler : public ClientHandler {

    Solver<P, S> *_solver;
    CacheManager<P, S> *_cm;

    bool sendMsg(int out, const char* msg) {
         int is_sent = send(out, msg, strlen(msg), 0);
         return is_sent != -1;
        return 2;
    }

public:
    MyTestClientHandler(Solver<P, S> *solver, CacheManager<P, S> *cm) {
        _solver = solver;
        _cm = cm;
    }

    ~MyTestClientHandler() override {
        delete _solver;
        delete _cm;
    }

    void handleClient(int in) override {
        while (true) {
            char buffer[1024] = {0};
            int valRead = read(in, buffer, 1024);

            if (valRead != 0 && valRead != -1) {
                if (strcmp(buffer, "end") != 0) {
                    string problem = buffer;

                    if (_cm->isSolutionExist(problem)) {
                        //solutionExist exist in cm, we return in to the client
                        string solutionExist = _cm->getSolution(problem);
                        if (!sendMsg(in, solutionExist.c_str())) {
                            cout << "Error sending message: " << solutionExist << endl;
                        }
                    } else {
                        //solutionNotExist dont exist in cm, we solve the problem and save it at cm
                        string solutionNotExist = _solver->solve(problem);
                        _cm->saveSolution(problem, solutionNotExist);
                        if (!sendMsg(in, solutionNotExist.c_str())) {
                            cout << "Error sending message: " << solutionNotExist << endl;
                        }
                    }
                } else {
                    //client wants to end communication
                    break;
                }
            } else {
                throw "ERROR: message from client did not receive";
            }
        }
    }
};

#endif //MILSTONE2__MYTESTCLIENTHANDLER_H_
