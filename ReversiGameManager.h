//
// Created by kostarubtsov1990 on 17/12/17.
//

#ifndef EX5SERVER_REVERSIGAMEMANAGER_H
#define EX5SERVER_REVERSIGAMEMANAGER_H

#include "GameManager.h"
#include "ActiveGame.h"
#include <map>
#include <string>

using namespace std;

class ReversiGameManager : public GameManager{
public:
    void StartNewGame (string name);
    void ListGames ();
    void JoinGame (string name);
    void PlayMove (int x, int y);
    void CloseGame (string name);
    void SetCurrentClientSocket (int currentClientSocket);

};


#endif //EX5SERVER_REVERSIGAMEMANAGER_H
