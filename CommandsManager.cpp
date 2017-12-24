//
// Created by kostarubtsov1990 on 24/12/17.
//

#include "CommandsManager.h"
#include "NewGameCommand.h"
#include "ReversiGameManager.h"
#include "ListGameCommand.h"
#include "JoinGameCommand.h"
#include "MakeStepCommand.h"
#include "CloseGameCommand.h"


CommandsManager::CommandsManager() {
    ReversiGameManager reversiManager;
    GameManager* manager = &reversiManager;

    commandsMap["start"] = new NewGameCommand(manager);
    commandsMap["list_games"] = new ListGameCommand(manager);
    commandsMap["join"] = new JoinGameCommand(manager);
    commandsMap["play"] = new MakeStepCommand(manager);
    commandsMap["close"] = new CloseGameCommand(manager);
}
void CommandsManager::ExecuteCommand(string command, vector<string> args) {
    Command *commandObj = commandsMap[command];
    commandObj->Execute(args);
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it !=
                                   commandsMap.end(); it++) {
        delete it->second;
    }
}