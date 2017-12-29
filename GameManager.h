/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

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
    vector <pthread_t> activeThreads;
    int currentClientSocket;
public:
    virtual void StartNewGame (string name) = 0;
    virtual void ListGames () = 0;
    virtual void JoinGame (string name) = 0;
    virtual void SetCurrentClientSocket (int currentClientSocket) = 0;
    void CloseClientSocketsRoutine();
};

#endif //EX5SERVER_GAMEMANAGER_H
