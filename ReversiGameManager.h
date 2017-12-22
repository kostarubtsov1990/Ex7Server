//
// Created by kostarubtsov1990 on 17/12/17.
//

#ifndef EX5SERVER_REVERSIGAMEMANAGER_H
#define EX5SERVER_REVERSIGAMEMANAGER_H

#include "GameManager.h"
#include "ActiveGame.h"
#include "PlayerAddress.h"
#include <map>
#include <string>

using namespace std;

class ReversiGameManager : public GameManager{
private:
    map <string, ActiveGame> nameToGameObject;
    map <PlayerAddress, string> addressToGameName;

public:


};


#endif //EX5SERVER_REVERSIGAMEMANAGER_H
