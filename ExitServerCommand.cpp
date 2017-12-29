/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#include "ExitServerCommand.h"
ExitServerCommand::ExitServerCommand(GameManager *manager) : Command(manager){}

void ExitServerCommand::Execute(vector<string> args) {
    manager->CloseClientSocketsRoutine();
}