//
// Created by kostarubtsov1990 on 24/12/17.
//

#ifndef EX5SERVER_CLOSEGAMECOMMAND_H
#define EX5SERVER_CLOSEGAMECOMMAND_H


#include "Command.h"

class CloseGameCommand : public Command{
public:
    CloseGameCommand (GameManager* manager);
    virtual void Execute (vector <string> args);
};


#endif //EX5SERVER_CLOSEGAMECOMMAND_H
