/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#ifndef EX5SERVER_EXITSERVERCOMMAND_H
#define EX5SERVER_EXITSERVERCOMMAND_H

#include <vector>
#include "string"
#include "Command.h"

using namespace std;

/*
 * This class will execute the receiver method
 * that is responsible for sending to all clients that the server is shutting down.
 * and then closing all the clients socket numbers.
 */
class ExitServerCommand : public Command{
public:
    ExitServerCommand(GameManager* manager);
    virtual void Execute (vector <string> args);
};


#endif //EX5SERVER_EXITSERVERCOMMAND_H
