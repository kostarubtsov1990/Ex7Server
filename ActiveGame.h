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
    int returnNthPlayer(int n);

};


#endif //EX5SERVER_ACTIVEGAME_H