cmake_minimum_required(VERSION 3.23)
project(BlackArt)

find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
