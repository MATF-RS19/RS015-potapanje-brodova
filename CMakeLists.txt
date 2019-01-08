cmake_minimum_required(VERSION 3.8)
project(Server)

set(CMAKE_CXX_STANDARD 11)

set(GENERAL_SOURCE_FILES Server/GameManager.cpp Server/GameManager.h Server/User.cpp Server/User.h Server/Game.cpp Server/Game.h Server/Helper.cpp Server/Helper.h)
set(SERVER_SOURCE_FILES Server/BattleshipServer.cpp Server/BattleshipServer.h)
set(TEST_SOURCE_FILES Server/main.cpp ${GENERAL_SOURCE_FILES} ${SERVER_SOURCE_FILES})
#set(TMP_SOURCE_FILES Server/server.cpp Server/client-test.cpp)
add_executable(Test ${TEST_SOURCE_FILES})
add_executable(Server ${GENERAL_SOURCE_FILES} ${SERVER_SOURCE_FILES})
#add_executable(Tmp ${TMP_SOURCE_FILES})

#find_library(Boost COMPONENTS system thread filesystem)
#find_package(cpprestsdk REQUIRED)

#target_link_libraries(Server PRIVATE cpprestsdk::cpprest)
#target_link_libraries(Tmp PRIVATE cpprestsdk::cpprest)
