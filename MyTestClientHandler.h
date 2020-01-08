//
// Created by guy on 08/01/2020.
//

#ifndef MILSTONE2__MYTESTCLIENTHANDLER_H_
#include <ostream>
#include "ClientHandler.h"
#define MILSTONE2__MYTESTCLIENTHANDLER_H_

class MyTestClientHandler : public ClientHandler {

  Solver* solver;
  CacheManager* cm;

 public:
  MyTestClientHandler(Solver* solver, CacheManager* cm);
  void handle(istream in, ostream out);
  void handleClient(istream in, ostream out) override;
  ~MyTestClientHandler() override;

};

#endif //MILSTONE2__MYTESTCLIENTHANDLER_H_
