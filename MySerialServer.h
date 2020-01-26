//
// Created by guy on 21/01/2020.
//

#ifndef MILSTONE2__MYSERIALSERVER_H_
#include "Server.h"
#define MILSTONE2__MYSERIALSERVER_H_
class MySerialServer : public server_side::Server {

 public:
  static bool isStop;
  int _socket;
  MySerialServer();
  static void start(int socket, sockaddr_in address, ClientHandler* c);
  void open(int port, ClientHandler* clientHandler) override;
  void stop() override;
  int getSocket();
  void setSocket(int socket);
  static void setTimeOut(int socket);
  static void setStop(bool isStop);
  virtual ~MySerialServer();
};

#endif //MILSTONE2__MYSERIALSERVER_H_
