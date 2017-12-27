//
// Created by kostarubtsov1990 on 27/12/17.
//

#include "ExitServerCommand.h"
ExitServerCommand::ExitServerCommand(GameManager *manager) : Command(manager){}

void ExitServerCommand::Execute(vector<string> args) {
    manager->CloseClientSocketsRoutine();
}