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
private:
    bool IsGameExist(string gameName);
public:
    virtual void StartNewGame (string name);
    virtual void ListGames ();
    virtual void JoinGame (string name);
    virtual void PlayMove (int x, int y);
    virtual void CloseGame (string name);
    virtual void SetCurrentClientSocket (int currentClientSocket);

};


#endif //EX5SERVER_REVERSIGAMEMANAGER_H
