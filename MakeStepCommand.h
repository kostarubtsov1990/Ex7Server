//
// Created by kostarubtsov1990 on 24/12/17.
//

#ifndef EX5SERVER_MAKESTEPCOMMAND_H
#define EX5SERVER_MAKESTEPCOMMAND_H


#include "Command.h"

class MakeStepCommand : public Command{
public:
    MakeStepCommand (GameManager* manager);
    virtual void Execute (vector <string> args);
};


#endif //EX5SERVER_MAKESTEPCOMMAND_H