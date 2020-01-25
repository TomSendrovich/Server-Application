//
// Created by tom5012 on 23/01/2020.
//

#include "MyParallelServer.h"
using namespace server_side;

#define TIMEOUT 30
bool MyParallelServer::isStop;
int MyParallelServer::clientCounter;
int MyParallelServer::_socket;

MyParallelServer::MyParallelServer() {
  isStop = false;
  clientCounter = 0;
}
void MyParallelServer::open(int port, ClientHandler* clientHandler) {
  //create socket
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) { throw "ERROR: cannot create a socket"; }

  setSocket(socketfd);

  //bind socket to IP address
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

//the bind command
  if (bind(socketfd, (struct sockaddr*) &address, sizeof(address)) == -1) {
    throw "ERROR: cannot bind to the IP address";
  }
  this->start(socketfd, address, clientHandler);
  //thread serverThread(start, socketfd, address, clientHandler);
  //serverThread.join();
  if (clientCounter == 0) {
    stop();
  }
}
void MyParallelServer::start(int socket, sockaddr_in address, ClientHandler* c) {
  //setTimeOut(socket);
  socklen_t size = sizeof(address);
  while (!isStop) {
    if (listen(socket, 10) == -1) {
      throw "ERROR: cannot make socket listen to the port";
    } else {
      //cout << "Server is now listening ..." << endl;
    }
    // accepting a client
    int clientSocket = accept(socket, (struct sockaddr*) &address, &size);
    if (clientSocket < 0) {
      if (EWOULDBLOCK) {
        cerr << "Time out" << endl;
        setStop(true);
        break;
      }
    }
    clientCounter++;
    //cout << "Client is now connected to server" << endl;
    try {
      thread handlingClient(handleOneClient, clientSocket, c->copy());
      handlingClient.detach();
    } catch (const char* e) {
      cerr << e << endl;
    }
  }
}
void MyParallelServer::handleOneClient(int clientSocket, ClientHandler* clientHandler) {
  clientHandler->handleClient(clientSocket);
  clientCounter--;
}
void MyParallelServer::stop() {
  close(getSocket());
}
void MyParallelServer::setSocket(int socket) { this->_socket = socket; }
void MyParallelServer::setTimeOut(int socket) {
  timeval timeout;
  timeout.tv_sec = TIMEOUT;
  timeout.tv_usec = 0;
  setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout, sizeof(timeout));
}
int MyParallelServer::getSocket() { return _socket; }
void MyParallelServer::setStop(bool state) { isStop = state; }

