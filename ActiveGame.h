/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#ifndef EX5SERVER_ACTIVEGAME_H
#define EX5SERVER_ACTIVEGAME_H

#include <vector>
using namespace std;

/*
 * this class represents an active game that holds its players
 * it supports adding a player, get number of players and get one of the players (its socket)
 */
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
