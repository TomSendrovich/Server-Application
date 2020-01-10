//
// Created by tom5012 on 08/01/2020.
//

#ifndef MILSTONE2_SERVER_H
#define MILSTONE2_SERVER_H

#include "ClientHandler.h"

namespace server_side {
class Server {
  //open the server and listening. wait for clients.
  virtual void open(int port, ClientHandler& clientHandler) = 0;

  //close the server.
  virtual void stop() = 0;
};
}
#endif //MILSTONE2_SERVER_H
