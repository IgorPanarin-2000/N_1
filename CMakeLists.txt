cmake_minimum_required (VERSION 2.8)

project (Convex)

set (CONVEX_SRC main.cpp convex.cpp list.cpp)
set (CONVEX_HDR convex.h list.h)

add_executable(${PROJECT_NAME} ${CONVEX_SRC} ${CONVEX_HDR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
