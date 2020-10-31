cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(runTests parserTest.cpp ../JSON.cpp ../Monster.cpp ../Hero.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
