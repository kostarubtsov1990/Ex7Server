//
// Created by kostarubtsov1990 on 17/12/17.
//

#ifndef EX5SERVER_REVERSIGAMEMANAGER_H
#define EX5SERVER_REVERSIGAMEMANAGER_H

#include "GameManager.h"
#include "ActiveGame.h"
#include <map>
#include <string>
#include <iostream>
#include <zconf.h>
#include <cstring>
#define BUF_SIZE 1024

enum player {firstPlayer, secondPlayer};
enum gameStatus {inProgress, finished};

//GameHandler is runned by thread
void* GameHandler(void *args);

//handle one transaction between two players in a game.
gameStatus handleDirection(int from, int to);

/*
 *this struct contains the sockets of two players in a game and a pointer to the
 * handleDirection function.
 *instance of this class is created in void ReversiGameManager::JoinGame(string name).
 *where it is passed as an argument to the GameHandler function that is runned in a thread
 */
typedef struct {
    int joinedPlayerClientSocket;
    int hostPlayerClientSocket;
    gameStatus (*handleDirection)(int, int);
} gameHandlerArgs;

using namespace std;

class ReversiGameManager : public GameManager{
private:
    template <class T, class U>
    bool IsKeyExist(T Key, map <T, U> mapToSearch);

public:
    virtual void StartNewGame (string name);
    virtual void ListGames ();
    virtual void JoinGame (string name);
    //To delete at last.
    /*virtual void PlayMove (int x, int y);
    virtual void CloseGame (string name);*/
    virtual void SetCurrentClientSocket (int currentClientSocket);

};


#endif //EX5SERVER_REVERSIGAMEMANAGER_H
