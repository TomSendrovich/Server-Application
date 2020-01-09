//
// Created by guy on 09/01/2020.
//

#ifndef MILSTONE2__MYSERIALSERVER_H_
#include "Server.h"
using namespace server_side;
#define MILSTONE2__MYSERIALSERVER_H_

class MySerialServer : public Server {
  void open(int port, ClientHandler clientHandler) override;
  void stop() override;
};

#endif //MILSTONE2__MYSERIALSERVER_H_
