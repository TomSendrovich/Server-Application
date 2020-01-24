//
// Created by guy on 09/01/2020.
//

#include "MySerialServer.h"
using namespace server_side;

#define TIMEOUT 30
bool MySerialServer::isStop;

MySerialServer::MySerialServer() { isStop = false; }
void MySerialServer::open(int port, ClientHandler* clientHandler) {
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

  thread serverThread(start, socketfd, address, clientHandler);
  serverThread.join();
  stop();
}
void MySerialServer::start(int socket, sockaddr_in address, ClientHandler* c) {
  //setTimeOut(socket);
  socklen_t size = sizeof(address);

  while (!isStop) {
    if (listen(socket, 1) == -1) {
      throw "ERROR: cannot make socket listen to the port";
    } else {
      cout << "Server is now listening ..." << endl;
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
    cout << "Client is now connected to server" << endl;
    try {
      c->handleClient(clientSocket);
    } catch (const char* e) {
      cerr << e << endl;
    }
  }
}
int MySerialServer::getSocket() { return _socket; }
void MySerialServer::setSocket(int socket) { this->_socket = socket; }
void MySerialServer::setStop(bool state) { isStop = state; }
void MySerialServer::setTimeOut(int socket) {
  timeval timeout;
  timeout.tv_sec = TIMEOUT;
  timeout.tv_usec = 0;
  setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout, sizeof(timeout));
}
void MySerialServer::stop() { close(getSocket()); }
