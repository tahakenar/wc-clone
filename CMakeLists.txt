cmake_minimum_required(VERSION 3.2)
project(wc VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(argh)

add_library(${PROJECT_NAME}_lib src/wc.cpp)
target_link_libraries(${PROJECT_NAME}_lib PUBLIC argh)
target_include_directories(${PROJECT_NAME}_lib PUBLIC include)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

enable_testing()

add_subdirectory(tests)