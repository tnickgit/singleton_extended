cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)

project(Singleton)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Singleton src/db.cpp src/main.cpp)

add_executable(my_test src/db.cpp test/test.cpp)

target_include_directories(my_test PRIVATE ${PROJECT_SOURCE_DIR}/include)

enable_testing()

add_test(NAME my_test COMMAND my_test)