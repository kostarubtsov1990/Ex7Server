/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#ifndef EX5SERVER_NEWGAMECOMMAND_H
#define EX5SERVER_NEWGAMECOMMAND_H

#include "GameManager.h"
#include "Command.h"

/*
 * NewGameCommand activates the corresponding function in the GameManager object.
 */
class NewGameCommand : public Command{
public:
    NewGameCommand(GameManager* manager);
    void Execute(vector <string> args);

};

#endif //EX5SERVER_NEWGAMECOMMAND_H
