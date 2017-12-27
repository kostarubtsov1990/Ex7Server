//
// Created by kostarubtsov1990 on 24/12/17.
//

#include "CommandsManager.h"
#include "NewGameCommand.h"
#include "ReversiGameManager.h"
#include "ListGameCommand.h"
#include "JoinGameCommand.h"
#include "ExitServerCommand.h"
#include <sstream>


CommandsManager::CommandsManager() {

    GameManager* manager = new ReversiGameManager;

    //Initiallize commandsMap with the possible commands that can be sent by client
    commandsMap["start"] = new NewGameCommand(manager);
    commandsMap["list_games"] = new ListGameCommand(manager);
    commandsMap["join"] = new JoinGameCommand(manager);
    commandsMap["exit_server"] = new ExitServerCommand(manager);
}

//activate the Execute object of the relevant command
void CommandsManager::ExecuteCommand(string command, vector<string> args) {
    //extracting the relevant command from the commandsMap.
    Command *commandObj = commandsMap[command];
    //this line will invoke the operation that handles the command sent by the client
    //(throught the ReversiGameManager object that each command holds.
    commandObj->Execute(args);
}

void CommandsManager::CommandHandler(int clientSocket, string dataFromClient) {
    ostringstream ss;
    ss << clientSocket;
    vector<string> args;
    args.push_back(ss.str());
    std::size_t foundIndex;
    string command;

    foundIndex = dataFromClient.find(' ');
    while (foundIndex != string::npos) {
        string subStr = dataFromClient.substr(0, foundIndex);
        dataFromClient = dataFromClient.substr(foundIndex + 1, dataFromClient.size() - foundIndex);
        if (subStr.find('<') != string::npos) {
            args.push_back(subStr);
        }
        else {
            command = subStr;
        }
        foundIndex = dataFromClient.find(' ');
    }

    if (dataFromClient.find('<') == string::npos) {
        command = dataFromClient;
    } else {
        args.push_back(dataFromClient);
    }

    for (int i = 1; i < args.size(); i++) {
        args[i] = args[i].substr(1, args[i].size() - 2);
    }

    ExecuteCommand(command, args);

}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it !=
                                   commandsMap.end(); it++) {
        delete it->second;
    }
}