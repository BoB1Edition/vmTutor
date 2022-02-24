cmake_minimum_required(VERSION 3.20)
project(vmParserParser)

set (CMAKE_CXX_STANDARD 17)

set(SOURCE ParserClass.cpp ast.cpp)

add_library(${PROJECT_NAME} ${SOURCE})

