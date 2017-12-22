//
// Created by kostarubtsov1990 on 22/12/17.
//

#ifndef EX5SERVER_MODIFIEDCOMMANDMAP_H
#define EX5SERVER_MODIFIEDCOMMANDMAP_H

#include <map>
#include <string>
#include "Command.h"
using namespace std;

class ModifiedCommandMap {
private:
    map <string,Command*> commandNameToCommand;
    string ExtractCommandName(string dataFromClient);
    void SetArgsToCommand(string argsString);
public:
    Command* GetCommand (string dataFromClient);
};


#endif //EX5SERVER_MODIFIEDCOMMANDMAP_H
