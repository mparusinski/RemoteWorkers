cmake_minimum_required(VERSION 2.8)

project(REMOTEWORKERS_CONTROLUNIT)
find_package(Qt4 REQUIRED)

add_subdirectory(Tests)
add_executable(remoteWorkers_ControlUnit main.cpp)
