//
// Created by kostarubtsov1990 on 24/12/17.
//

#include <cstdlib>
#include "CloseGameCommand.h"

CloseGameCommand::CloseGameCommand(GameManager *manager) : Command::Command(manager){}

void CloseGameCommand::Execute(vector <string> args) {
    //args[0] will be the client's socket integer.
    manager->SetCurrentClientSocket(atoi(args[0].c_str()));
    //args[1] will be the name string of the game.
    manager->CloseGame(args[1]);
}