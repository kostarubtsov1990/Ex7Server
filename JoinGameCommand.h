//
// Created by kostarubtsov1990 on 24/12/17.
//

#ifndef EX5SERVER_JOINGAMECOMMAND_H
#define EX5SERVER_JOINGAMECOMMAND_H


#include "Command.h"

class JoinGameCommand : public Command{
public:
    JoinGameCommand (GameManager* manager);
    virtual void Execute (vector <string> args);
};


#endif //EX5SERVER_JOINGAMECOMMAND_H
