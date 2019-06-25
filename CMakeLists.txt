cmake_minimum_required(VERSION 3.0)
project(test)
set(HEADER_FILES Include/Game.hpp Include/World.hpp Include/Player.hpp Include/Bunker.hpp Include/Fuel.hpp Include/Projectile.hpp Include/ProjectileHandler.hpp Include/TextNode.hpp Include/ResourceHolder.hpp)
set(SOURCE_FILES Source/Game.cpp Source/World.cpp Source/Player.cpp Source/Bunker.cpp Source/Fuel.cpp Source/Projectile.cpp Source/ProjectileHandler.cpp Source/TextNode.cpp Source/ResourceHolder.cpp)
add_library(mylib ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(mylib PRIVATE Include)
add_executable(Gravitar Source/Main.cpp ${HEADER_FILES})
target_include_directories(Gravitar PRIVATE Include)
target_link_libraries(Gravitar mylib)
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(Gravitar ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

