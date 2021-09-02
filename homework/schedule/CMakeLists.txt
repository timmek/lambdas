cmake_minimum_required(VERSION 3.10)
project(schedule)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(.)

add_executable(${PROJECT_NAME} main.cpp)
add_executable(${PROJECT_NAME}-ut tests/catch_amalgamated.cpp tests/catch_main.cpp tests/tests.cpp)
add_executable(${PROJECT_NAME}-ut-bonus tests/catch_amalgamated.cpp tests/catch_main.cpp tests/tests-bonus.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)
target_compile_options(${PROJECT_NAME}-ut PRIVATE -Wall -Wextra -Werror -Wpedantic)
target_compile_options(${PROJECT_NAME}-ut-bonus PRIVATE -Wall -Wextra -Werror -Wpedantic)

enable_testing()
add_test(NAME schedule-tests COMMAND ${PROJECT_NAME}-ut)
