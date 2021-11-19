cmake_minimum_required(VERSION 3.5.1)

# set the project name
project(Glitch VERSION 1.0)

# add the executable
add_executable(${PROJECT_NAME} main.cpp)

# specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# defining glitch library
add_library(glitch src/glitch.cpp)
target_include_directories(glitch PUBLIC "${PROJECT_SOURCE_DIR}/include")

# linking libraries to executable
target_link_libraries(${PROJECT_NAME} PUBLIC glitch)