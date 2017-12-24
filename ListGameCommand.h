//
// Created by kostarubtsov1990 on 22/12/17.
//

#ifndef EX5SERVER_LISTGAMECOMMAND_H
#define EX5SERVER_LISTGAMECOMMAND_H


#include "Command.h"

class ListGameCommand : public Command{
public:
    ListGameCommand (GameManager* manager);
    void Execute(vector <string> args);
};


#endif //EX5SERVER_LISTGAMECOMMAND_H
