cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# TODO: rename project and delete this comment
project(lab-02-cache)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

# TODO: change template word to project name and delete this comment
add_executable(lab-02-cache
        # enum your files and delete this comment
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Experiment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Investigation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/lab2.cpp
        )

# TODO: change template word to project name and delete this comment
target_include_directories(lab-02-cache
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
