//
// Created by kostarubtsov1990 on 22/12/17.
//

#ifndef EX5SERVER_NEWGAMECOMMAND_H
#define EX5SERVER_NEWGAMECOMMAND_H

#include "GameManager.h"
#include "Command.h"

class NewGameCommand : public Command{
private:
    string name;
public:
    NewGameCommand(GameManager* manager, void(GameManager:: *method)());
    void Execute(int port, string IP);
    void SetArgs (string args []);

};


#endif //EX5SERVER_NEWGAMECOMMAND_H
