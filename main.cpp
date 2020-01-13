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
        static int main(int argc, char *argv[]) {
            int port = atoi(argv[1]);
            Solver<P, S> *solver = new StringReverser<P, S>();
            CacheManager<P, S> *fileCacheManager = new FileCacheManager<P, S>(CACHE_SIZE);
            ClientHandler *myTestClientHandler = new MyTestClientHandler<P, S>(solver, fileCacheManager);

            Server *mySerialServer = new MySerialServer();
            mySerialServer->open(port, *myTestClientHandler);

            return 1;
        }
    };
}

using namespace boot;

int main(int argc, char *argv[]) {
    boot::Main<string, string> main;
    return main.main(argc, argv);
}
