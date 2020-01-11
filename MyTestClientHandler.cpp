//
// Created by guy on 08/01/2020.
//

#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include "MyTestClientHandler.h"

MyTestClientHandler::MyTestClientHandler(Solver *solver, CacheManager *cm) : solver(solver), cm(cm) {}

//todo: implement method
void MyTestClientHandler::handle(int in, int out) {

}

bool MyTestClientHandler::sendMsg(int out, const char *msg) {
    int is_sent = send(out, msg, strlen(msg), 0);
    return is_sent != -1;
}

void MyTestClientHandler::handleClient(int in, int out) {
    while (true) {
        char buffer[1024] = {0};
        int valRead = read(in, buffer, 1024);
        if (valRead != 0 && valRead != -1) {
            auto *problem = new Problem(buffer);
            if (strcmp(buffer, "end") != 0) {
                if (cm->isSolutionExist(buffer)) {
                    //solutionExist exist in cm, we return in to the client
                    auto *solutionExist = new Solution(cm->getSolution(problem->getProblem().c_str()));
                    if (!sendMsg(out, solutionExist->getSolution().c_str())) {
                        cout << "Error sending message: " << solutionExist->getSolution() << endl;
                    }
                } else {
                    //solutionNotExist dont exist in cm, we solve the problem and save it at cm
                    Solution *solutionNotExist = solver->solve(*problem);
                    cm->saveSolution(buffer, solutionNotExist->getSolution().c_str());
                    if (!sendMsg(out, solutionNotExist->getSolution().c_str())) {
                        cout << "Error sending message: " << solutionNotExist->getSolution() << endl;
                    }
                }
            } else {
                //client want to end communication
                break;
            }
        } else {
            throw "ERROR: message from client did not receive";
        }
    }

    //handle(in, out);
}

MyTestClientHandler::~MyTestClientHandler() {
    delete solver;
    delete cm;
}
