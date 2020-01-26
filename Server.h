//
// Created by tom5012 on 08/01/2020.
//

#ifndef MILSTONE2_SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include "ClientHandler.h"
#define CACHE_SIZE 10

#define MILSTONE2_SERVER_H

namespace server_side {
class Server {
 public:
  //open the server and listening. wait for clients.
  virtual void open(int port, ClientHandler* clientHandler) = 0;

  //close the server.
  virtual void stop() = 0;

  virtual ~Server();
};

}

#endif //MILSTONE2_SERVER_H
