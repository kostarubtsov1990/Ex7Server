//
// Created by kostarubtsov1990 on 22/12/17.
//

#include <cstdlib>
#include "ListGameCommand.h"

ListGameCommand::ListGameCommand(GameManager *manager) : Command::Command(manager){}

void ListGameCommand::Execute(vector <string> args) {
    //args[0] will be the client's socket integer.
    manager->SetCurrentClientSocket(atoi(args[0].c_str()));
    //args[1] will be the name string of the game.
    manager->ListGames();
}