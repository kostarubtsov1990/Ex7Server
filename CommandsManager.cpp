/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#include "CommandsManager.h"
#include "NewGameCommand.h"
#include "ReversiGameManager.h"
#include "ListGameCommand.h"
#include "JoinGameCommand.h"
#include "ExitServerCommand.h"
#include <sstream>

CommandsManager::CommandsManager() {
    this->manager = new ReversiGameManager;

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
    //Convert int to string and add the socket to args vector.
    ostringstream ss;
    ss << clientSocket;
    vector<string> args;
    args.push_back(ss.str());
    std::size_t foundIndex;
    string command;
    bool first = true;

    //Split the data that received from the client by spaces and save it to args vector.
    foundIndex = dataFromClient.find(' ');
    while (foundIndex != string::npos) {
        string subStr = dataFromClient.substr(0, foundIndex);
        dataFromClient = dataFromClient.substr(foundIndex + 1, dataFromClient.size() - foundIndex);
        if (!first) {
            args.push_back(subStr);
        }
        else {
            first = false;
            command = subStr;
        }
        foundIndex = dataFromClient.find(' ');
    }
    if (!first) {
        args.push_back(dataFromClient);
    } else {
        command = dataFromClient;

    }

    //This function will execute the concrete command from the commandMap taken by the command string key.
    //with the appropriate args
    ExecuteCommand(command, args);
}

CommandsManager::~CommandsManager() {
    delete this->manager;
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it !=
                                   commandsMap.end(); it++) {
        delete it->second;
    }
}