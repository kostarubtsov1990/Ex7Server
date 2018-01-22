/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;
#define MAX_CONNECTED_CLIENTS 10
#define BUF_SIZE 1024

Server::Server(CommandsManager* commMap) {
    //Read the settings from file.
    const char* fileName = "settings.txt";
    string ip;
    string portString;
    ifstream myfile(fileName);
    getline(myfile, ip);
    getline(myfile, portString);

    port = atoi(portString.c_str());
    commandMap = commMap;

    //this will be the amount threads that will execute the tasks
    pool = new ThreadPool(MAX_CONNECTED_CLIENTS);
}

Server::Server(int port): port(port), serverSocket(0) {
    cout << "Server" << endl;
}

void Server::start() {
    //Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    //Asign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void*)&serverAddress,sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    int n = listen(serverSocket,MAX_CONNECTED_CLIENTS);
    if (n) {
        throw "Error on listening";
    }

    pthread_t thread;
    /*
     *create a thread that will run the AcceptClientHandler method. this thread will be responsible
     *to listening clients connections and will run in an infinite loop that will allocate a thread
     *every time a client is connected. this thread will handle the command string that this client is about to send.
      */
    acceptHandlerArgs *args = new acceptHandlerArgs;
    args->serverSocket = serverSocket;
    args->commandMap = commandMap;
    args->activeThreads = &activeThreads;
    args->pool = pool;

    int result = pthread_create(&thread, NULL, AcceptClientHandler, args);

    if (result) {
        cout << "Error: unable to create thread, " << result << endl;
        exit(-1);
    }
    //Add thread that runs  AcceptClientHandler function to list of active threads.
    activeThreads.push_back(thread);

    string exitCommand;
    //Wait for exit command from the server side user.
    cin >> exitCommand;

    while (exitCommand != "exit") {
        cin >> exitCommand;
    }

    //handlerArgs content was copied to ClientArgs content so handlerArgs isnt necessary anymore
    delete args;

    //send message to each client that server is about to shut down, and close all sockets of connected clients
    commandMap->CommandHandler(0, "exit_server");
    pool->Terminate();
    delete pool;
}

/*
 * this method is invoked immediately after client is connected to the server, and
 * it runs in a seperate thread.
 * It gets the socket of the client and expects to get strings in the following possible formats:
 * start <name>
 * list_games
 * join <name>
 *
 * in each case, the CommandHandler method (of the CommandManager object) will be invoked
 * (with the client's socket and one of the above strings' format).
 * The CommandHandler will extract the specific command object.
 * Through the GameManager object, that each command object holds, the relevant operation will be performed.
 */
void* ClientHandler(void *args) {
    clientHandlerArgs* handlerArgs = (clientHandlerArgs*)args;
    char clientQueryBuffer[BUF_SIZE];
    int playerClientSocket = handlerArgs->clientSocket;
    int n = read(playerClientSocket, clientQueryBuffer, sizeof(clientQueryBuffer));
    //If client sends list_game command, after the client receive the game list
    //the server closes the connection with the client.
    if (n == 0) {
        exit(-1);
    }
    /*handle the commands string that the client has just sent:
     *parsing client's input, call ExecuteCommand method of CommandsManager.cpp,
     *that will activate Execute method of the specific command.
     * the Execute method of the specific command will call the correct method in ReversiGameManager.cpp.
     */
    handlerArgs->commandMap->CommandHandler(playerClientSocket, clientQueryBuffer);

    vector <pthread_t>::iterator toErase = find(handlerArgs->activeThreads->begin(), handlerArgs->activeThreads->end(), pthread_self());
    if(toErase != handlerArgs->activeThreads->end())
        handlerArgs->activeThreads->erase(toErase);
    delete handlerArgs;
    //here the thread is dead (after the corresponding function in reversiGameManager is finished)
}

/*
 * this method is called from the start method of this class.
 * it keeps listening to connections for optional clients. Once a client is connected,
 * a thread that handles the possible commands that the client can send, is allocated for him.
 * Meanwhile, the server keeps listening to new connections of clients
 */
void* AcceptClientHandler(void *args) {
    acceptHandlerArgs* handlerArgs = (acceptHandlerArgs*)args;

    while (true) {
        cout << "Waiting for client connection...." << endl;
        //Define the client socket's structures
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLen = sizeof(clientAddress);
        //after this line, client is connected to server (send him a message that he is connected?)
        int playerClientSocket = accept(handlerArgs->serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
        if (playerClientSocket == -1) {
            cout << "Error: unable to accept client " << endl;
            exit(-1);
        }
        //pthread_t thread;

        clientHandlerArgs* clientArgs = new clientHandlerArgs;
        clientArgs->clientSocket = playerClientSocket;
        clientArgs->commandMap = handlerArgs->commandMap;
        clientArgs->activeThreads = handlerArgs->activeThreads;

        /*create a thread that runs the ClientHandler function.
        *ClientHandler function is responsible for handling possible commands
        */

        Task* task = new Task(ClientHandler, clientArgs);
        handlerArgs->pool->AddTask(task);

        /*int result = pthread_create(&thread, NULL, ClientHandler, clientArgs);
        if (result) {
            cout << "Error: unable to create thread, " << result << endl;
            exit(-1);
        }*/
        //handlerArgs->activeThreads->push_back(thread);


    }


}

void Server::stop() {
    for (int i=0; i < activeThreads.size(); i++) {
        if (pthread_cancel(activeThreads[i])) {
            cout << "Error: unable to cancel a thread" << endl;
            exit(-1);
        }
    }
    delete commandMap;
}