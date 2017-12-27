//
// Created by kostarubtsov1990 on 27/12/17.
//

#ifndef EX5SERVER_EXITSERVERCOMMAND_H
#define EX5SERVER_EXITSERVERCOMMAND_H

#include <vector>
#include "string"
#include "Command.h"

using namespace std;


class ExitServerCommand : public Command{
public:
    ExitServerCommand(GameManager* manager);
    virtual void Execute (vector <string> args);
};


#endif //EX5SERVER_EXITSERVERCOMMAND_H
