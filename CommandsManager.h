/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#ifndef EX5SERVER_COMMANDSMANAGER_H
#define EX5SERVER_COMMANDSMANAGER_H

#include <string>
#include "Command.h"

class CommandsManager {
public:
    CommandsManager();
    ~CommandsManager();
    /*
     * separates between the command name and the arguments the are passed
     * to the command, from the Client side.
     * afterwards, activate Execute method with the command itself, its arguments and the client's socket
     * - all are passed to ExecuteCommand in a vector.
     */
    void CommandHandler (int clientSocket, string dataFromClient);
private:
    GameManager* manager;
    /*
     * ExecuteCommand extracts the concrete command object according to the command string,
     * then, it activates the Execute method of the concrete command
     */
    void ExecuteCommand(string command, vector<string> args);
    map<string, Command *> commandsMap;
};

#endif //EX5SERVER_COMMANDSMANAGER_H
