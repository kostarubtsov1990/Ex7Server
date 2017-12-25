//
// Created by kostarubtsov1990 on 17/12/17.
//

#include <zconf.h>
#include <cstring>
#include "ReversiGameManager.h"

void ReversiGameManager::StartNewGame(string name) {

    string message;

    if (IsKeyExist<string, ActiveGame>(name, nameToGameObject)) {
        message = "-1";
        //Game with this name exist to ask client to choose another name.
        int n = write(currentClientSocket, message.c_str(), strlen(message) + 1);
        return;
    }

    socketToGameName[currentClientSocket] = name;

    ActiveGame activeGame;
    activeGame.AddPlayer(currentClientSocket);

    nameToGameObject[name] = activeGame;

    message = "game_created_successfully";

    int n = write(currentClientSocket, message.c_str(), strlen(message) + 1);
}

void ReversiGameManager::JoinGame(string name) {
    string message;

    if (!IsKeyExist<string, ActiveGame>(name, nameToGameObject)) {
        message = "game_not_exist";
        //Game with this name exist to ask client to choose another name.
        int n = write(currentClientSocket, message.c_str(), strlen(message) + 1);
        return;
    }



    string gameName = socketToGameName[currentClientSocket];
    ActiveGame activeGame = nameToGameObject[gameName];


    if (activeGame.GetNumOfPlayers() > 1) {
        message = "game_is_full";
        //Game with this name exist to ask client to choose another name.
        int n = write(currentClientSocket, message.c_str(), strlen(message) + 1);
        return;
    }


    message = "joined_to_game";

    activeGame.AddPlayer(currentClientSocket);

    int n = write(currentClientSocket, message.c_str(), strlen(message) + 1);

    pthread_t thread;
    int result = pthread_create(&thread, NULL, ClientHandler, (void *) &playerClientSocket);



}

void ReversiGameManager::ListGames() {

    string message;

    //Append all the game names to a message.
    map<string, ActiveGame>::iterator it;
    for (it = nameToGameObject.begin(); it != nameToGameObject.end(); it++) {
        message += (it->first + "\n");
    }

    int n = write(currentClientSocket, message.c_str(), strlen(message) + 1);
}

void ReversiGameManager::PlayMove(int x, int y) {

    string message;


    if (!IsKeyExist<int , string>(currentClientSocket, socketToGameName)) {
        message = "game_not_exist";
        //Game with this name exist to ask client to choose another name.
        int n = write(currentClientSocket, message.c_str(), strlen(message) + 1);
        return;
    }

    string gameName = socketToGameName[currentClientSocket];
    ActiveGame activeGame = nameToGameObject[gameName];

    int opponentSocket = activeGame.ReturnOpponentPlayerSocket(currentClientSocket);

    int n = write(opponentSocket, &x, sizeof(x));
    //To add failure conditions.
    n = write(opponentSocket, &y, sizeof(y));

}

void ReversiGameManager::CloseGame(string name) {
    string message;


    if (!IsKeyExist<int , string>(currentClientSocket, socketToGameName)) {
        message = "you_have_no_active_game";
        //Game with this name exist to ask client to choose another name.
        int n = write(currentClientSocket, message.c_str(), strlen(message) + 1);
        return;
    }


    string gameName = socketToGameName[currentClientSocket];

    if (gameName != name) {
        message = "no_permission_to_close_that_game";
        //Game with this name exist to ask client to choose another name.
        int n = write(currentClientSocket, message.c_str(), strlen(message) + 1);
        return;
    }

    ActiveGame activeGame = nameToGameObject[gameName];

    //TO DO: continue writing closing routine


}

void* ReversiGameManager::GameHandler(void *args) {
    int joinedPlayerClientSocket = *(int*)args;

    string gameName = socketToGameName[joinedPlayerClientSocket];
    ActiveGame activeGame = nameToGameObject[gameName];

    int hostPlayerClientSocket = activeGame.ReturnOpponentPlayerSocket(joinedPlayerClientSocket);

    gameStatus status;
    //if status equals "finished", game is over and server keeps listening to connections from clients.
    while (status != finished) {
        //first player sends its move, second player updates its own board with the first player's move, and moves too.
        status = handleDirection(hostPlayerClientSocket, joinedPlayerClientSocket);

        if (status == finished)
            break;
        //sec passes its choose to the first player that updates its board according to the second's move, and
        //the first makes its own move.
        status = handleDirection(joinedPlayerClientSocket, hostPlayerClientSocket);
    }
    nameToGameObject.erase(gameName);
    socketToGameName.erase(joinedPlayerClientSocket);
    socketToGameName.erase(hostPlayerClientSocket);
}

gameStatus ReversiGameManager::handleDirection(int from, int to) {
    char clientQueryBuffer [BUF_SIZE];
    //read (x,y) move performed by client1
    int n = read(from, clientQueryBuffer, sizeof(clientQueryBuffer));
    //handle errors
    if (n == -1) {
        cout << "Error reading arg1" << endl;
        return finished;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return finished;
    }
    //send (x,y) move performed by client1 to client2
    n = write(to, clientQueryBuffer, sizeof(clientQueryBuffer));
    //handle errors
    if (n == -1) {
        cout << "Error reading arg1" << endl;
        return finished;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return finished;
    }
    //game is finished
    if (strcmp(clientQueryBuffer, "END") == 0) {
        return finished;
    }
}

template <class T, class U>
bool ReversiGameManager::IsKeyExist(T Key, map <T, U> mapToSearch) {
    map<T, U>::iterator it;
    for (it = mapToSearch.begin(); it != mapToSearch.end(); it++) {
        if (it->first == Key) {
            return true;
        }
    }
    return false;
}





