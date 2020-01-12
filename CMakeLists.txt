cmake_minimum_required(VERSION 3.15)
project(Milstone2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Milstone2
        CacheManager.h
        ClientHandler.h
        FileCacheManager.h
        main.cpp
        MySerialServer.cpp
        MySerialServer.h
        MyTestClientHandler.h
        Server.h
        Solver.h
        StringReverser.h
        )
