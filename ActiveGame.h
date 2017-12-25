//
// Created by kostarubtsov1990 on 22/12/17.
//

#ifndef EX5SERVER_ACTIVEGAME_H
#define EX5SERVER_ACTIVEGAME_H

#include <vector>

using namespace std;

class ActiveGame {
private:
    vector <int> currentPlayers;
public:
    int ReturnNthPlayer(int n);
    void AddPlayer (int playerSocket);
    int GetNumOfPlayers ();
    int ReturnOpponentPlayerSocket (int currentPlayerSocket);

};


#endif //EX5SERVER_ACTIVEGAME_H
