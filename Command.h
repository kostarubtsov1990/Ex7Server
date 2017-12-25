//
// Created by kostarubtsov1990 on 22/12/17.
//

#ifndef EX5SERVER_COMMAND_H
#define EX5SERVER_COMMAND_H

#include <string>
#include "GameManager.h"

using namespace std;

class Command {
protected:
    GameManager* manager;
public:
    virtual void Execute (vector <string> args) = 0;
};


#endif //EX5SERVER_COMMAND_H
