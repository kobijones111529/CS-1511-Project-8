cmake_minimum_required(VERSION 3.10)

project(Project8)

set(SOURCES
    # Main
    src/main.cpp

    src/item.cpp
    src/bag.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)