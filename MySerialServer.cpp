//
// Created by guy on 09/01/2020.
//

#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include "Server.h"

#define TIMEOUT 30

//todo: consider move this 'isStop' field to header file as data member
bool isStop;

void server_side::MySerialServer::open(int port, ClientHandler &clientHandler) {
    isStop = false;
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) { throw "ERROR: cannot create a socket"; }
    //bind socket to IP address
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);

    //the bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        throw "ERROR: cannot bind to the IP address";
    }

    //making socket listen to the port
    if (listen(socketfd, 1) == -1) { //can also set to SOMAXCON (max connections)
        throw "ERROR: cannot make socket listen to the port";
    }

    thread listenThread(listenToClients, socketfd,address, ref(clientHandler));
    listenThread.join();
    close(socketfd);
}

void server_side::MySerialServer::listenToClients(int socketfd, sockaddr_in address, ClientHandler &clientHandler) {
    socklen_t size = sizeof(address);
    struct timeval tv;
    tv.tv_sec = TIMEOUT;
    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
    long inSocket;

    while (!isStop) {
        cout << "Server is now listening ..." << endl;


        // accepting a client
         inSocket = accept(socketfd, (struct sockaddr *) &address, &size);
        if (inSocket == -1) { throw "ERROR: cannot accept client"; }

        cout << "Client is now connected to server" << endl;
        handleClient(inSocket,ref(clientHandler));

    }//end of while loop
}

void server_side::MySerialServer::handleClient(int inSocket, ClientHandler &clientHandler) {
    clientHandler.handleClient(inSocket);
}

void server_side::MySerialServer::stop() { isStop = true; }
