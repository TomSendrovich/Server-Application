//
// Created by tom5012 on 23/01/2020.
//

#ifndef MILSTONE2__MYPARALLELSERVER_H_
#include <netinet/in.h>
#include "Server.h"
#define MILSTONE2__MYPARALLELSERVER_H_

class MyParallelServer : public server_side::Server {
 public:
  static bool isStop;
  static int _socket,clientCounter;
  MyParallelServer();

  static void start(int socket, sockaddr_in address, ClientHandler* c);
  void open(int port, ClientHandler* clientHandler) override;
  void stop() override;
  int getSocket();
  void setSocket(int socket);
  static void setTimeOut(int socket);
  static void setStop(bool isStop);
  static void handleOneClient(int clientSocket, ClientHandler* clientHandler);
};

#endif //MILSTONE2__MYPARALLELSERVER_H_
