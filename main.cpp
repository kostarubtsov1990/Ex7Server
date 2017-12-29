/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#include <iostream>
#include <stdlib.h>
#include "Server.h"

using namespace std;

int main() {
    //create server and pass to it CommandManager object
    Server server(new CommandsManager());
    try {
        server.start();
        server.stop();
    }
    catch (const char* msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    return 0;
}