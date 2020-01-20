cmake_minimum_required(VERSION 3.15)
project(Milstone2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Milstone2 BestFirstSearch.h CacheManager.h ClientHandler.h FileCacheManager.h main.cpp
        MatrixProblem.h MySerialServer.cpp MyTestClientHandler.h Searchable.h Searcher.h Server.h Solver.h State.h
        StringReverser.h Position.h Cell.h Cell.cpp State.cpp Solution.cpp Solution.h BestFirstSearch.cpp
        CacheManager.cpp ClientHandler.cpp FileCacheManager.cpp MatrixProblem.cpp MyTestClientHandler.cpp
        Position.cpp Searchable.cpp Searcher.cpp Server.cpp Solver.cpp StringReverser.cpp MyClientHandler.cpp
        MyClientHandler.h ObjectAdapter.cpp ObjectAdapter.h BreadthFirstSearch.cpp BreadthFirstSearch.h)
