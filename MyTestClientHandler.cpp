//
// Created by guy on 08/01/2020.
//

#include "MyTestClientHandler.h"

MyTestClientHandler::MyTestClientHandler(Solver* solver, CacheManager* cm) : solver(solver), cm(cm) {}
//todo: implement method
void MyTestClientHandler::handle(int in, int out) {}
void MyTestClientHandler::handleClient(int in, int out) { handle(in, out); }
MyTestClientHandler::~MyTestClientHandler() {
  delete solver;
  delete cm;
}
