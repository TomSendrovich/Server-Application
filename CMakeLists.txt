cmake_minimum_required(VERSION 3.15)
project(Milstone2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Milstone2
        main.cpp
        ClientHandler.h
        MyTestClientHandler.cpp
        MyTestClientHandler.h
        Solver.h
        CacheManager.h
        Solution.cpp
        Solution.h
        Problem.cpp
        Problem.h
        Server.h)
