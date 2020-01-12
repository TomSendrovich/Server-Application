#include <iostream>
#include "Server.h"
#include "MySerialServer.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "ClientHandler.h"
#include "MyTestClientHandler.h"
#include "Solver.h"
#include "StringReverser.h"
#define CACHE_SIZE 5

namespace boot {
template<class P, class S>
class Main {
 public:
  static int main(int argc, char* argv[]) {
    int port = atoi(argv[1]);
    Solver<P, S>* solver = new StringReverser<P, S>();
    CacheManager<P, S>* fileCacheManager = new FileCacheManager<P, S>(CACHE_SIZE);
    ClientHandler* myTestClientHandler = new MyTestClientHandler<P, S>(solver, fileCacheManager);

    Server* mySerialServer = new MySerialServer();
    mySerialServer->open(port, *myTestClientHandler);

/*    fileCacheManager->saveSolution("1", "tom sendrovich");
    fileCacheManager->saveSolution("2", "guy shoham");
    fileCacheManager->saveSolution("3", "ofir cohen");
    fileCacheManager->saveSolution("4", "hila bartov");
    fileCacheManager->saveSolution("5", "tzivka the king");
    fileCacheManager->saveSolution("6", "i dont mind");

    const char* problem = "3";
    string solution;
    bool isExist = fileCacheManager->isSolutionExist(problem);
    if (isExist) {
      cout << "true" << endl;
      solution = fileCacheManager->getSolution(problem);
      cout << solution << endl;
    } else {
      cout << "false" << endl;
    }*/

    return 1;
  }
};
}

using namespace boot;

int main(int argc, char* argv[]) {
//  Main<string, string>* main = new Main<string, string>();
//  return main->main(argc, argv);
}
