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
    void(GameManager:: *method)();
public:
    virtual void Execute (int port, string IP) = 0;
    virtual void SetArgs (string args []) = 0;
};


#endif //EX5SERVER_COMMAND_H
