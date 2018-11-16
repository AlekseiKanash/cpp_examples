cmake_minimum_required(VERSION 3.1)

project(cppexamplestest)

set ( sources
    main.cpp
    LambdasAndContainers.cpp
    FunctionsUsage.cpp
)

set ( libs
    stdc++
)

set ( headers
    FunctionsUsage.h
    LambdasAndContainers.h
)

set(LIBRARY_OUTPUT_PATH lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} ${libs})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

