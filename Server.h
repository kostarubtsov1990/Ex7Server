//
// Created by kostarubtsov1990 on 04/12/17.
//

#ifndef EX4SERVER_SERVER_H
#define EX4SERVER_SERVER_H

#include "CommandsManager.h"

/*
 * these functions will be run by threads:
 * ClientHandler function is run by thread from Server.cpp: void* AcceptClientHandler(void *args)
 * AcceptClientHandler is run by thread from: void Server::start()
 */
void* ClientHandler(void *args);
void* AcceptClientHandler(void *args);


typedef struct {
    int serverSocket;
    vector <int> *clientSockets;
    CommandsManager* commandMap;
    vector <pthread_t> *activeThreads;

} acceptHandlerArgs;

typedef struct {
    int clientSocket;
    CommandsManager* commandMap;
    vector <pthread_t> *activeThreads;
    vector <int> *clientSockets;
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
    vector <pthread_t> activeThreads;
    void CloseRoutine();
    //int connectPlayer (player player);
};


#endif //EX4SERVER_SERVER_H
