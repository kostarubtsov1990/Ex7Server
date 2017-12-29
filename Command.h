/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#ifndef EX5SERVER_COMMAND_H
#define EX5SERVER_COMMAND_H

#include <string>
#include "GameManager.h"
using namespace std;

/*
 * Command (=Invoker) holds pointer to GameManager object (=receiver) and execute
 * one of the methods of the receiver.
 * Each concrete command will activate the corresponding method of the GameManager according
 * to its responsibility
 */
class Command {
protected:
    GameManager* manager;
public:
    Command (GameManager* manager);
    virtual void Execute (vector <string> args) = 0;
};

#endif //EX5SERVER_COMMAND_H
