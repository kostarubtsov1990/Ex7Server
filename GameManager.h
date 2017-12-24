//
// Created by kostarubtsov1990 on 17/12/17.
//

#ifndef EX5SERVER_GAMEMANAGER_H
#define EX5SERVER_GAMEMANAGER_H
#include <string>
#include <map>
#include "ActiveGame.h"

using namespace std;

class GameManager {
protected:
    //Game list
    map <string, ActiveGame> nameToGameObject;
    map <int , string> socketToGameName;
    int currentClientSocket;
public:
    virtual void StartNewGame (string name) = 0;
    virtual void ListGames () = 0;
    virtual void JoinGame (string name) = 0;
    virtual void PlayMove (int x, int y) = 0;
    virtual void CloseGame (string name) = 0;
    virtual void SetCurrentClientSocket (int currentClientSocket) = 0;
};


#endif //EX5SERVER_GAMEMANAGER_H
