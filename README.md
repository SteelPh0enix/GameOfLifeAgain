# Game of Life - again

This is my implementation of John Conway's Game of Life.
Right now, it's in very early alpha stage, so don't expect much features implemented.

## Features (to be done/in progress)

* Setting custom rules of the Game
* Creating boards with any size
* Custom colour schemes
* Camera support (zooming and moving over the board)
* Custom simulation speed support

## Used technologies

* C++17 - main language
* Raylib - drawing and input handling
* Dear ImGUI - user interface
* spdlog - program logs

## Building the game

Use CMake. External libraries are handled using variables:

* `RAYLIB_DIR` - install directory of Raylib, with the `lib/` and `include/` dirs.
* `SPDLOG_DIR` - source dir of spdlog, with `src/` and `include/` dirs
* `IMGUI_DIR` - source dif or ImGUI, with `*.cpp` files

Set them up, generate the project and it should work fine.