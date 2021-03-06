/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#include <cstdlib>
#include <algorithm>
#include "ReversiGameManager.h"

void ReversiGameManager::StartNewGame(string name) {
    string message;
    //check if the requested game exists
    if (IsKeyExist<string, ActiveGame>(name, nameToGameObject)) {
        message = "-1";
        //Game with this name exist to ask client to choose another name.
        int n = write(currentClientSocket, message.c_str(), strlen(message.c_str()) + 1);
        if (n == -1) {
            cout << "Error" << endl;
        }
        if (n == 0) {
            cout << "No Connection" << endl;
        }
        return;
    }
    //game exists. attach client's socket to game's name (using socketToGameName map)
    socketToGameName[currentClientSocket] = name;
    //create new object for activeGame andd add the client to its vector of players.
    ActiveGame activeGame;
    activeGame.AddPlayer(currentClientSocket);

    //attaching game's name to the game object using the nameToGameObject map.
    nameToGameObject[name] = activeGame;

    message = "game_created_successfully";
    //notify the client that a new game was created successfully.
    int n = write(currentClientSocket, message.c_str(), strlen(message.c_str()) + 1);
    if (n == -1) {
        cout << "Error" << endl;
    }
    if (n == 0) {
        cout << "No Connection" << endl;
    }
}

void ReversiGameManager::JoinGame(string name) {
    string message;
    //check if the requested game exists.
    if (!IsKeyExist<string, ActiveGame>(name, nameToGameObject)) {
        message = "game doesnt exist!\n";
        //Game with this name exist to ask client to choose another name.
        int n = write(currentClientSocket, message.c_str(), strlen(message.c_str()) + 1);
        if (n == -1) {
            cout << "Error" << endl;
        }
        if (n == 0) {
            cout << "No Connection" << endl;
        }
        return;
    }

    //using the gameName, extract the game object from the nameToGameObject map.
    ActiveGame activeGame = nameToGameObject[name];

    //game is occupied. ask the client to join another game
    if (activeGame.GetNumOfPlayers() > 1) {
        message = "game is full!\n";
        //Game with this name exist to ask client to choose another name.
        int n = write(currentClientSocket, message.c_str(), strlen(message.c_str()) + 1);
        if (n == -1) {
            cout << "Error" << endl;
        }
        if (n == 0) {
            cout << "No Connection" << endl;
        }
        return;
    }

    socketToGameName[currentClientSocket] = name;

    //add the client to the game by pushing its socket to the players' vector.
    activeGame.AddPlayer(currentClientSocket);
    nameToGameObject[name] = activeGame;

    message = "joined_to_game";
    //send the client a message indicating that he joined successfully to the game that he asked to join.
    int n = write(currentClientSocket, message.c_str(), strlen(message.c_str()) + 1);
    if (n == -1) {
        cout << "Error" << endl;
    }
    if (n == 0) {
        cout << "No Connection" << endl;
    }

    /*
     * create a thread that will run the function GameHandler. From now on, two players
     * can play the reversiGame.
     */
    pthread_t thread;
    //joined player id
    int joinedPlayerClientSocket = currentClientSocket;
    //first player id
    int hostPlayerClientSocket = activeGame.ReturnOpponentPlayerSocket(joinedPlayerClientSocket);

    /*struct that holds the sockets of both players and pointer to the handleDirection function
     *this struct will be sent as an argument to the function GameHandler. GameHandler is a function
     * that will be run by the following thread.
     */
    gameHandlerArgs* handlerArgs = new gameHandlerArgs;
    handlerArgs->joinedPlayerClientSocket = currentClientSocket;
    handlerArgs->hostPlayerClientSocket = hostPlayerClientSocket;
    handlerArgs->handleDirection = handleDirection;

    /*
     *here a thread that will run the GameHandler function is created.
     * Actually, this thread handles a game between two clients. GameHandler has all the necessary
     * information to handle a game properly - socket of first client, socket of the client that joined
     * to the game, and pointer to the function handleDirection that responsible for transaction between one
     * client to another.
     */
    int result = pthread_create(&thread, NULL, GameHandler, handlerArgs);
    if (result) {
        cout << "Error: unable to create thread, " << result << endl;
        exit(-1);
    }

    activeThreads.push_back(thread);
    void *status;
    /*
     * block the ClientHandler thread. Actually, the thread that runs the ClientHandler function, waits on this line
     * till the thread that runs GameHandler dies (=the game it handles is over).
     */
    if (pthread_join(thread, &status)) {
        cout << "Error: unable to do pthread_join" << endl;
    }

    vector <pthread_t>::iterator toErase = find(activeThreads.begin(), activeThreads.end(), thread);
    if(toErase != activeThreads.end())
        activeThreads.erase(toErase);

    //the thread that runs the ClientHandler function removes the game's name (=key) and the game (=ActiveGame)
    nameToGameObject.erase(name);
    //remove (joined player socket, game's name)
    socketToGameName.erase(joinedPlayerClientSocket);
    //remove (jost player socket, game's name)
    socketToGameName.erase(hostPlayerClientSocket);
}

void ReversiGameManager::ListGames() {
    string message;

    //Append all the game names to a message.
    map<string, ActiveGame>::iterator it;

    if (nameToGameObject.empty()) {
        message = "No games are available\n";
    }
    else {
        for (it = nameToGameObject.begin(); it != nameToGameObject.end(); it++) {
            if (it->second.GetNumOfPlayers() == 1) {
                message += (it->first + "\n");
            }
        }
    }
    //send a string with active games (not necessariliy games that the client can join)
    int n = write(currentClientSocket, message.c_str(), strlen(message.c_str()) + 1);
    if (n == -1) {
        cout << "Error" << endl;
    }
    if (n == 0) {
        cout << "No Connection" << endl;
    }
    //Close client connection (in order to avoid resources' wasting, since client might not ask to join a game)
    close(currentClientSocket);
}

void* GameHandler(void *args) {
    gameHandlerArgs* handlerArgs = (gameHandlerArgs*)args;

    //Send the clients notification about starting the game.
    string message = "start_game";
    //send start_game message to the player who opened the game
    int n = write(handlerArgs->hostPlayerClientSocket, message.c_str(), strlen(message.c_str()) + 1);
    if (n == -1) {
        cout << "Error" << endl;
    }
    if (n == 0) {
        cout << "No Connection with host player" << endl;
    }
    //send start message to the player who joined the game
    n = write(handlerArgs->joinedPlayerClientSocket, message.c_str(), strlen(message.c_str()) + 1);
    if (n == -1) {
        cout << "Error" << endl;
    }
    if (n == 0) {
        cout << "No Connection with the player who joined" << endl;
    }

    gameStatus status;
    //if status equals "finished", game is over and server keeps listening to connections from clients.
    while (status != finished) {
        //first player sends its move, second player updates its own board with the first player's move, and moves too.
        status = handlerArgs->handleDirection(handlerArgs->hostPlayerClientSocket, handlerArgs->joinedPlayerClientSocket);

        if (status == finished)
            break;
        //sec passes its choose to the first player that updates its board according to the second's move, and
        //the first makes its own move.
        status = handlerArgs->handleDirection(handlerArgs->joinedPlayerClientSocket, handlerArgs->hostPlayerClientSocket);
    }
}

gameStatus handleDirection(int from, int to) {
    char clientQueryBuffer [BUF_SIZE];
    //read (x,y) move performed by client1
    int n = read(from, clientQueryBuffer, sizeof(clientQueryBuffer));
    //handle errors
    if (n == -1) {
        cout << "Error reading arg1" << endl;
        return finished;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return finished;
    }
    //send (x,y) move performed by client1 to client2
    n = write(to, clientQueryBuffer, sizeof(clientQueryBuffer));
    //handle errors
    if (n == -1) {
        cout << "Error reading arg1" << endl;
        return finished;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return finished;
    }
    //game is finished
    if (strcmp(clientQueryBuffer, "END") == 0) {
        return finished;
    }
}

//given a key and a map, check if the map contains the specified key or not.
template <class T, class U>
bool ReversiGameManager::IsKeyExist(T Key, map <T, U> mapToSearch) {
    typename map<T, U>::iterator it;
    for (it = mapToSearch.begin(); it != mapToSearch.end(); it++) {
        if (it->first == Key) {
            return true;
        }
    }
    return false;
}

void ReversiGameManager::SetCurrentClientSocket(int clientSocket) {
    currentClientSocket = clientSocket;
}