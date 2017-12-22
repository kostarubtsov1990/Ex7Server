//
// Created by kostarubtsov1990 on 22/12/17.
//

#ifndef EX5SERVER_PLAYERADDRESS_H
#define EX5SERVER_PLAYERADDRESS_H

#include <string>
using namespace std;


class PlayerAddress {

private:
    int port;
    string IP;
public:
    PlayerAddress(int port, string IP);
    int GetPort ();
    string GetIP();
};


#endif //EX5SERVER_PLAYERADDRESS_H
