cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(violet C)

add_subdirectory(lib/Unity-2.5.2/) # testing framework
add_subdirectory(lib/qlibc/)
add_subdirectory(lib/cglm/)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb3 -pg")

file(GLOB_RECURSE SOURCES src/*.c)
set(HEADERS
  include/
  lib/qlibc/include
  lib/cglm/include
  lib/sokol/
)

# This is the main part:
add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERS})
target_link_libraries(${PROJECT_NAME} m qlibc glfw cglm GL dl)

add_executable(gameoflife main.c)
target_link_libraries(gameoflife ${PROJECT_NAME})
target_include_directories(gameoflife PUBLIC ${HEADERS})

add_subdirectory(test/)
