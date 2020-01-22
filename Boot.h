//
// Created by guy on 21/01/2020.
//

#ifndef MILSTONE2__BOOT_H_
#include "MySerialServer.h"
#include "FileCacheManager.h"
#include "MyClientHandler.h"
#include "ObjectAdapter.h"
#include "BestFirstSearch.h"
#include "MatrixProblem.h"
#include "Cell.h"
#define MILSTONE2__BOOT_H_

namespace boot {
using namespace server_side;
class Main {
 public:
  Main() {}

  static int main(int port) {
    auto* searcher = new BestFirstSearch<Cell*>(); ///switch algorithm here
    auto* solver =  new ObjectAdapter<MatrixProblem, string, Cell*>(searcher);;
    auto* cacheManager = new FileCacheManager(CACHE_SIZE);
    auto* clientHandler = new MyClientHandler<MatrixProblem, string>(solver, cacheManager);
    auto* server = new MySerialServer();
    server->open(port, clientHandler);

    return 1;
  }
};
}

#endif //MILSTONE2__BOOT_H_
