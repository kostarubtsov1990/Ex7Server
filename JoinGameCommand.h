/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#ifndef EX5SERVER_JOINGAMECOMMAND_H
#define EX5SERVER_JOINGAMECOMMAND_H

#include "Command.h"

/*
 * This class will execute the receiver method
 * it adds the socket of the client that joins, to the map (socket to string) in GameManager,
 * then it extracts ActiveGame object from map (string to ActiveGame), and finally it adds it to ActiveGame's vector.
 */
class JoinGameCommand : public Command{
public:
    JoinGameCommand (GameManager* manager);
    virtual void Execute (vector <string> args);
};

#endif //EX5SERVER_JOINGAMECOMMAND_H
