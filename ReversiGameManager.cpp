//
// Created by kostarubtsov1990 on 17/12/17.
//

#include <zconf.h>
#include <cstring>
#include "ReversiGameManager.h"

void ReversiGameManager::StartNewGame(string name) {

    string message;

    if (IsGameExist(name)) {
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

    if (!IsGameExist(name)) {
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

}

void ReversiGameManager::CloseGame(string name) {

}

bool ReversiGameManager::IsGameExist(string gameName) {
    map<string, ActiveGame>::iterator it;
    for (it = nameToGameObject.begin(); it != nameToGameObject.end(); it++) {
        if (it->first == gameName) {
            return true;
        }
    }
    return false;
}




