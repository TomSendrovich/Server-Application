//
// Created by tom5012 on 08/01/2020.
//

#ifndef MILSTONE2_SERVER_H

#include <netinet/in.h>
#include "ClientHandler.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "Solver.h"
#include "StringReverser.h"
#define CACHE_SIZE 5

#define MILSTONE2_SERVER_H

namespace server_side {
class Server {
 public:
  //open the server and listening. wait for clients.
  virtual void open(int port, ClientHandler& clientHandler) = 0;

  //close the server.
  virtual void stop() = 0;
};

class MySerialServer : public Server {
  static void listenToClients(int socketfd, sockaddr_in address, ClientHandler& clientHandler);
  static void handleClient(int inSocket, ClientHandler& clientHandler);

 public:
  void open(int port, ClientHandler& clientHandler) override;
  void stop() override;
};
}

namespace boot {
using namespace server_side;
template<typename P, typename S>
class Main {
 public:
  static int main(int argc, char* argv[]) {
    if (argc < 2) {
      cout << "You forgot to insert port number!" << endl;
      return 0;
    }
    int port = atoi(argv[1]);
    Solver<P, S>* solver = new StringReverser<P, S>();
    CacheManager<P, S>* fileCacheManager = new FileCacheManager<P, S>(CACHE_SIZE);
    ClientHandler* myTestClientHandler = new MyTestClientHandler<P, S>(solver, fileCacheManager);

    Server* mySerialServer = new MySerialServer();
    mySerialServer->open(port, *myTestClientHandler);

    return 1;
  }
};
}
#endif //MILSTONE2_SERVER_H
