cmake_minimum_required(VERSION 2.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

project(rngGameJam)
add_executable(RNG
  KeyClicks.cpp
  KeyClicks.h
  MainMenu.cpp
  MainMenu.h
  PlayLevel.cpp
  PlayLevel.h
  TileGrid.cpp
  TileGrid.h
  Entity.cpp
  Entity.h
  Player.cpp
  Player.h
  Enemy.cpp
  Enemy.h
  ColiderRect.cpp
  ColiderRect.h
  UserInterface.cpp
)

target_link_libraries(RNG sfml-system sfml-graphics sfml-window sfml-audio)
