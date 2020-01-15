//
// Created by guy on 09/01/2020.
//

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include "Server.h"
#define TIMEOUT 120

//todo: consider move this 'isStop' field to header file as data member
bool isStop;

void server_side::MySerialServer::open(int port, ClientHandler& clientHandler) {
  isStop = false;
  thread listenThread(listenToClients, port, ref(clientHandler));
  listenThread.join();
}
void server_side::MySerialServer::listenToClients(int port, ClientHandler& clientHandler) {
  while (!isStop) {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) { throw "ERROR: cannot create a socket"; }
    //bind socket to IP address
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);

    //the bind command
    if (bind(socketfd, (struct sockaddr*) &address, sizeof(address)) == -1) {
      throw "ERROR: cannot bind to the IP address";
    }

    //making socket listen to the port
    if (listen(socketfd, 1) == -1) { //can also set to SOMAXCON (max connections)
      throw "ERROR: cannot make socket listen to the port";
    } else { cout << "Server is now listening ..." << endl; }

    struct timeval tv;
    tv.tv_sec = TIMEOUT;
    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*) &tv, sizeof tv);

    // accepting a client
    socklen_t size = sizeof(address);
    int inSocket = accept(socketfd, (struct sockaddr*) &address, &size);
    if (inSocket == -1) { throw "ERROR: cannot accept client"; }

    cout << "Client is now connected to server" << endl;
    //reading from client
    thread handleClientThread(handleClient, inSocket, ref(clientHandler));
    handleClientThread.join();

    close(socketfd); //closing the listening socket
  }//end of while loop
}
void server_side::MySerialServer::handleClient(int inSocket, ClientHandler& clientHandler) {
  clientHandler.handleClient(inSocket);
}
void server_side::MySerialServer::stop() { isStop = true; }
