cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lambdas)

add_executable(area area.cpp)
add_executable(dangling dangling.cpp)
add_executable(synchronization synchronization.cpp)
add_executable(sfinae sfinae.cpp)

target_link_libraries(synchronization pthread)
