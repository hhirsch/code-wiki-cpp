cmake_minimum_required(VERSION 3.10)
project(xnextevent)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(X11 REQUIRED)
INCLUDE_DIRECTORIES(${X11_INCLUDE_DIRS})
add_executable(xnextevent main.cpp)
target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
