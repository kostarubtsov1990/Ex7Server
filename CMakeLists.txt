cmake_minimum_required(VERSION 3.8)
project(Ex7Server)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS -pthread)

set(SOURCE_FILES main.cpp Server.cpp Server.h GameManager.cpp GameManager.h ReversiGameManager.cpp ReversiGameManager.h Command.cpp Command.h NewGameCommand.cpp NewGameCommand.h ActiveGame.cpp ActiveGame.h ListGameCommand.cpp ListGameCommand.h CommandsManager.cpp CommandsManager.h JoinGameCommand.cpp JoinGameCommand.h ExitServerCommand.cpp ExitServerCommand.h Task.cpp Task.h ThreadPool.cpp ThreadPool.h)
add_executable(Ex7Server ${SOURCE_FILES})