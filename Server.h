//
// Created by kostarubtsov1990 on 04/12/17.
//

#ifndef EX4SERVER_SERVER_H
#define EX4SERVER_SERVER_H

#include "CommandsManager.h"

void* ClientHandler(void *args);
void* AcceptClientHandler(void *args);

typedef struct {
    int serverSocket;
    vector <int> clientSockets;
    CommandsManager* commandMap;
} acceptHandlerArgs;

typedef struct {
    int clientSocket;
    CommandsManager* commandMap;
} clientHandlerArgs;

class Server {
public:

    Server(CommandsManager* commandMap);
    Server(int port);
    void start();
    void stop();

private:
    int port;
    int serverSocket; // the socket's file descriptor
    CommandsManager* commandMap;
    vector <int> clientSockets;

    //int connectPlayer (player player);
};


#endif //EX4SERVER_SERVER_H
