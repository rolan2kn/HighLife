cmake_minimum_required(VERSION 3.15)
project(HighLife)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp  HighLife.cpp)
set(HEADER_FILES HighLife.h)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})

#Include library files
include_directories(include)

include_directories(GL/)

add_executable(HighLife ${SOURCE_FILES} ${HEADER_FILES} )

target_link_libraries(HighLife GL GLU glut )

