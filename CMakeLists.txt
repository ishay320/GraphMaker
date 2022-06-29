cmake_minimum_required(VERSION 3.10)

project(GraphMaker
        DESCRIPTION "Creates graph of the cpp/c project"
        VERSION 0.1

        # LANGUAGE    CXX
)

set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_VERBOSE_MAKEFILE ON)
list(APPEND packeges "utils.cpp" "utils.h")
list(APPEND packeges "graphMaker.cpp" "graphMaker.h")

add_executable(main main.cpp
        ${packeges})
