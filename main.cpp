#include <iostream>
#include "CacheManager.h"
#include "MySerialServer.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "Solver.h"
#include "StringReverser.h"
#include "Server.h"

#define CACHE_SIZE 5
namespace boot {
class Main {
 public:
  static int main(int argc, char* argv[]) {
    int port = atoi(argv[1]);
    Solver* solver = new StringReverser();
    CacheManager* fileCacheManager = new FileCacheManager(CACHE_SIZE);
    ClientHandler* myTestClientHandler = new MyTestClientHandler(solver, fileCacheManager);

    Server* mySerialServer = new MySerialServer();
    mySerialServer->open(port, *myTestClientHandler);

//    fileCacheManager->saveSolution("1", "tom sendrovich");
//    fileCacheManager->saveSolution("2", "guy shoham");
//    fileCacheManager->saveSolution("3", "ofir cohen");
//    fileCacheManager->saveSolution("4", "hila bartov");
//    fileCacheManager->saveSolution("5", "tzivka the king");
//    fileCacheManager->saveSolution("6", "i dont mind");

//    const char* problem = "3";
//    string solution;
//    bool isExist = fileCacheManager->isSolutionExist(problem);
//    if (isExist) {
//      cout << "true" << endl;
//      solution = fileCacheManager->getSolution(problem);
//      cout << solution << endl;
//    } else {
//      cout << "false" << endl;
//    }

    return 1;
  }
};
}
using namespace boot;

int main(int argc, char* argv[]) {
  Main* main = new Main();
  return main->main(argc, argv);
}
