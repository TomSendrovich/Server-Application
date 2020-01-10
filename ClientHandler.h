//
// Created by guy on 08/01/2020.
//

#ifndef MILSTONE2__CLIENTHANDLER_H_
#include <iostream>
using namespace std;
#define MILSTONE2__CLIENTHANDLER_H_

class ClientHandler {
 public:
  virtual void handleClient(int in, int out) = 0;
  virtual ~ClientHandler() = default;
};

#endif //MILSTONE2__CLIENTHANDLER_H_
