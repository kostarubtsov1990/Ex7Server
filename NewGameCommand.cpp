//
// Created by kostarubtsov1990 on 22/12/17.
//

#include <cstdlib>
#include "NewGameCommand.h"


NewGameCommand::NewGameCommand(GameManager *manager) : Command::Command(manager){}

void NewGameCommand::Execute(vector <string> args) {
    //args[0] will be the client's socket integer.
    manager->SetCurrentClientSocket(atoi(args[0].c_str()));
    //args[1] will be the name string of the game.
    manager->StartNewGame(args[1]);
}
