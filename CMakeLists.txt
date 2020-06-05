cmake_minimum_required(VERSION 3.16)
project(Students_Manager C)

set(CMAKE_C_STANDARD 11)
include_directories(include)
include_directories(libgraph/include)

FILE(GLOB_RECURSE LIBGRAPH_INCLUDE libgraph/include/*.h)
FILE(GLOB_RECURSE LIBGRAPH_SOURCES libgraph/src/*.c)

FILE(GLOB_RECURSE CURRENT_INCLUDE include/*.h)
FILE(GLOB_RECURSE CURRENT_SOURCES src/*.c)

add_executable(StuManager ${CURRENT_SOURCES} ${CURRENT_INCLUDE} ${LIBGRAPH_INCLUDE} ${LIBGRAPH_SOURCES} libgraph/include/initial.h)  #制定生成目标
