//
// Created by kostarubtsov1990 on 04/12/17.
//

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdlib>


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
    listen(serverSocket,MAX_CONNECTED_CLIENTS);


    pthread_t thread;
    /*
     *create a thread that will run the AcceptClientHandler method. this thread will be responsible
     *to listening clients connections and will run in an infinite loop that will allocate a thread
     *every time a client is connected. this thread will handle the command string that this client is about to send.
      */
    int result = pthread_create(&thread, NULL, AcceptClientHandler, NULL);

    if (result) {
        cout << "Error: unable to create thread, " << result << endl;
        exit(-1);
    }

    string exitCommand;

    //Wait for exit command from the server side user.
    cin >> exitCommand;

    while (exitCommand != "exit") {
        cin >> exitCommand;
    }

    //TO DO: stop the accept thread and also inform clients about server termination
    //TO DO: close all the client threads

}

int Server::connectPlayer(player player) {
    string massage;

    if (player == firstPlayer)
        massage = "wait_for_opponent";
    else
        massage = "Wait_for_first_move";

    //Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);


    //Accept a new client connection
    int playerClientSocket = accept(serverSocket,(struct sockaddr*)&clientAddress, &clientAddressLen);

    if (playerClientSocket == -1)
        throw "Error on accept first client";

    if (player == firstPlayer)
        cout << "first player connected" << endl;
    else
        cout << "second player connected" << endl;

    //send message to the relevant player
    int n = write(playerClientSocket, massage.c_str(), strlen(massage.c_str()) + 1);

    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return -1;
    }
    return playerClientSocket;
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
void* Server::ClientHandler(void *args) {
    while (true) {
        char clientQueryBuffer[BUF_SIZE];
        int *playerClientSocket = (int *) args;
        int n = read(*playerClientSocket, clientQueryBuffer, sizeof(clientQueryBuffer));
        //If client sends list_game command, after the client receive the game list
        //the server closes the connection with the client.
        if (n == 0) {
            break;
        }
        //handle the commands string that the client has just sent.
        commandMap->CommandHandler(*playerClientSocket, clientQueryBuffer);
    }
}

/*
 * this method is called from the start method of this class.
 * it keeps listening to connections for optional clients. Once a client is connected,
 * a thread that handles the possible commands that the client can send, is allocated for him.
 * Meanwhile, the
 */
void* Server::AcceptClientHandler(void *args) {
    while (true) {
        cout << "Waiting for client connection...." << endl;

        //Define the client socket's structures
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLen = sizeof(clientAddress);
        //after this line, client is connected to server (send him a message that he is connected?)
        int playerClientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);

        pthread_t thread;
        //create a thread that runs the ClientHandler method
        int result = pthread_create(&thread, NULL, ClientHandler, (void *) &playerClientSocket);

        if (result) {
            cout << "Error: unable to create thread, " << result << endl;
            exit(-1);
        }
    }
}


void Server::stop() {}