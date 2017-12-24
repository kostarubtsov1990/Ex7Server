
#include <iostream>
#include <stdlib.h>

#include "Server.h"
#include "NewGameCommand.h"
#include "ReversiGameManager.h"

using namespace std;

int main() {

    Server server(new CommandsManager());
    try {
        server.start();
    }
    catch (const char* msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    return 0;
}