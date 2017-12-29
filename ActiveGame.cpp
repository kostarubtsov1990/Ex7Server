/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#include "ActiveGame.h"

int ActiveGame::ReturnNthPlayer(int n) {
    return this->currentPlayers[n];
}

void ActiveGame::AddPlayer(int playerSocket) {
    this->currentPlayers.push_back(playerSocket);
}

int ActiveGame::GetNumOfPlayers() {
    return this->currentPlayers.size();
}

int ActiveGame::ReturnOpponentPlayerSocket(int currentPlayerSocket) {
    //Case where only two players are playing
    if (currentPlayers[0] == currentPlayerSocket) {
        return currentPlayers[1];
    }
    else {
        return currentPlayers[0];
    }
}
