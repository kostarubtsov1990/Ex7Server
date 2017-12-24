//
// Created by kostarubtsov1990 on 24/12/17.
//

#ifndef EX5SERVER_COMMANDSMANAGER_H
#define EX5SERVER_COMMANDSMANAGER_H

#include <string>
#include "Command.h"

class CommandsManager {
public:
    CommandsManager();
    ~CommandsManager();
    void CommandHandler (int clientSocket, string dataFromClient);
private:
    void ExecuteCommand(string command, vector<string> args);
    map<string, Command *> commandsMap;
};


#endif //EX5SERVER_COMMANDSMANAGER_H
