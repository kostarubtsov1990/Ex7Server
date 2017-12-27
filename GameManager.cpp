//
// Created by kostarubtsov1990 on 17/12/17.
//

#include <unistd.h>
#include "GameManager.h"

void GameManager::CloseClientSocketsRoutine() {
    typename map<int , string>::iterator it;
    for (it = socketToGameName.begin(); it != socketToGameName.end(); it++) {
        write(it->first, "server_shutdown", sizeof("server_shutdown"));
        close(it->first);
    }
}