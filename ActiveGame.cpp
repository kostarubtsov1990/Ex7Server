//
// Created by kostarubtsov1990 on 22/12/17.
//

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
