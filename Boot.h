//
// Created by guy on 21/01/2020.
//

#ifndef MILSTONE2__BOOT_H_
#include "MySerialServer.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#define MILSTONE2__BOOT_H_

namespace boot {
using namespace server_side;
class Main {
 public:
  Main() {}

  static int main(int port) {
    Solver<string, string>* solver = new StringReverser();
    CacheManager<string, string>* cacheManager = new FileCacheManager<string, string>(CACHE_SIZE);
    ClientHandler* clientHandler = new MyTestClientHandler<string, string>(solver, cacheManager);

    Server* server = new MySerialServer();
    server->open(port, clientHandler);

    return 1;
  }
};
}

#endif //MILSTONE2__BOOT_H_
