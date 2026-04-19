cmake_minimum_required(VERSION 3.21)
project(pi_stress_test CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
)

FetchContent_MakeAvailable(doctest)

add_library(pi_lib STATIC pi_lib.cpp)
target_include_directories(pi_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(stress_pi stress_pi.cpp)
target_link_libraries(stress_pi pi_lib)

add_executable(stress_pi_test stress_pi_test.cpp)
target_link_libraries(stress_pi_test pi_lib doctest)

enable_testing()
add_test(NAME stress_pi_test COMMAND stress_pi_test)