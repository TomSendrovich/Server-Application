//
// Created by guy on 08/01/2020.
//

#ifndef MILSTONE2__MYTESTCLIENTHANDLER_H_
#include <ostream>
#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#define MILSTONE2__MYTESTCLIENTHANDLER_H_

class MyTestClientHandler : public ClientHandler {

  Solver* solver;
  CacheManager* cm;

 public:
  MyTestClientHandler(Solver* solver, CacheManager* cm);
  void handle(int in, int out);
  void handleClient(int in, int out) override;
  bool sendMsg (int out, const char* msg);
  ~MyTestClientHandler() override;

};

#endif //MILSTONE2__MYTESTCLIENTHANDLER_H_
