cmake_minimum_required(VERSION 3.8)
project(Ex5Server)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Server.cpp Server.h GameManager.cpp GameManager.h ReversiGameManager.cpp ReversiGameManager.h Command.cpp Command.h NewGameCommand.cpp NewGameCommand.h ModifiedCommandMap.cpp ModifiedCommandMap.h ActiveGame.cpp ActiveGame.h ListGameCommand.cpp ListGameCommand.h CommandsManager.cpp CommandsManager.h JoinGameCommand.cpp JoinGameCommand.h MakeStepCommand.cpp MakeStepCommand.h CloseGameCommand.cpp CloseGameCommand.h)
add_executable(Ex5Server ${SOURCE_FILES})