cmake_minimum_required(VERSION 3.10)
project(thingsm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(SOURCES 
    src/main.cpp 

    # Header file
    src/utils.cpp
    src/appReset.cpp
    src/dataManager.cpp

    # Library
    src/sqlite3.c 
    src/bcrypt.cpp
    src/blowfish.cpp
)


add_executable(thingsm ${SOURCES})

# Specify external dependencies directories for .h files
target_include_directories(thingsm PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/dependencies
)



