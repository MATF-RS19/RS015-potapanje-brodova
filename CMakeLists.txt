cmake_minimum_required(VERSION 3.8)
project(Server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Server/main.cpp Server/GameManager.cpp Server/GameManager.h Server/User.cpp Server/User.h Server/Game.cpp Server/Game.h)
add_executable(Server ${SOURCE_FILES})