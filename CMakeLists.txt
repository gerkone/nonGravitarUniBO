cmake_minimum_required(VERSION 3.0)
project(test)
set(HEADER_FILES Include/Game.hpp Include/World.hpp Include/Player.hpp)
set(SOURCE_FILES Source/Game.cpp Source/World.cpp Source/Player.cpp)
add_library(mylib ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(mylib PRIVATE Include)
add_executable(myexec Source/Main.cpp ${HEADER_FILES})
target_include_directories(myexec PRIVATE Include)
target_link_libraries(myexec mylib)
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(myexec ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

