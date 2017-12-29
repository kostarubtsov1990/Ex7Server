//
// Created by kostarubtsov1990 on 17/12/17.
//

#include <unistd.h>
#include <cstring>
#include "GameManager.h"
#include "algorithm"

void GameManager::CloseClientSocketsRoutine() {
    typename map<int , string>::iterator it;
    for (it = socketToGameName.begin(); it != socketToGameName.end(); it++) {
        string message = "server_shutdown";
        write(it->first, message.c_str(), strlen(message.c_str()) + 1);
        close(it->first);
    }

    for (int i=0; i < activeThreads.size(); i++) {
        pthread_cancel(activeThreads[i]);
    }
}