//
// Created by guy on 08/01/2020.
//

#include "MyTestClientHandler.h"

MyTestClientHandler::MyTestClientHandler(Solver* solver, CacheManager* cm) : solver(solver), cm(cm) {
}

//todo: implement method
void MyTestClientHandler::handle(istream in, ostream out) {

}

void MyTestClientHandler::handleClient(istream in, ostream out) {
  handle(in,out);
}
MyTestClientHandler::~MyTestClientHandler() {
  delete solver;
  delete cm;
}
