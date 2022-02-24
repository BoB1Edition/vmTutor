cmake_minimum_required(VERSION 3.20)
project(vmCompile)
#SET (CMAKE_C_COMPILER             "/usr/bin/clang")
#SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
set (CMAKE_CXX_STANDARD 17)
set(DEBUG true)

set(SOURCE_EXE main.cpp)

if(CMAKE_BUILD_TYPE EQUAL "DEBUG")
  option(DEBUG "Enable debug" ON)
endif()
configure_file(configure.h.in ${CMAKE_SOURCE_DIR}/configure.h)

#set(GETTOK gettok.cpp)
#add_library(gettok STATIC ${GETTOK})

#set(BINOP gettok.cpp)
#add_library(binop STATIC ${BINOP})

#set(AST Clases.cpp)
#add_library(ast STATIC ${AST})

add_subdirectory(ParserClass)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_EXE})

target_link_libraries(${CMAKE_PROJECT_NAME} vmParserParser)