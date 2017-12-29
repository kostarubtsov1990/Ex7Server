/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#ifndef EX5SERVER_LISTGAMECOMMAND_H
#define EX5SERVER_LISTGAMECOMMAND_H

#include "Command.h"

/*
 * this class is responisible to execute the method ListGame of GameManager
 * that will pass to the Client all the available games on server.
 */
class ListGameCommand : public Command{
public:
    ListGameCommand (GameManager* manager);
    void Execute(vector <string> args);
};

#endif //EX5SERVER_LISTGAMECOMMAND_H
