/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "GameManager.h"

void GameManager::CloseClientSocketsRoutine() {
    typename map<int , string>::iterator it;
    for (it = socketToGameName.begin(); it != socketToGameName.end(); it++) {
        string message = "server_shutdown";
        int n = write(it->first, message.c_str(), strlen(message.c_str()) + 1);
        if (n == 0) {
            cout << "Error: No Connection with Client" << endl;
        }
        if (n == -1) {
            cout << "Error while executing write function" << endl;
        }
        if (close(it->first)) {
            cout << "Error: fail to close socket" << endl;
        }
    }
    //stop all the threads that run GameHandler function
    for (int i=0; i < activeThreads.size(); i++) {
        if (pthread_cancel(activeThreads[i])) {
            cout << "pthread_cancel error" << endl;
        }
    }
}