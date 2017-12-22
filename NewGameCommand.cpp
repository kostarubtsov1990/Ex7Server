//
// Created by kostarubtsov1990 on 22/12/17.
//

#include "NewGameCommand.h"
#include "PlayerAddress.h"

NewGameCommand::NewGameCommand(GameManager *manager, void(GameManager:: *method)())
        : manager(manager), method(method){}

void NewGameCommand::Execute(int port, string IP) {
    PlayerAddress address (port, IP);
    (manager-> *method)(address, name);
}

void NewGameCommand::SetArgs(string args []) {
    name = args[0];
}
