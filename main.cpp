/*
 * Copyright 2021 SteelPh0enix
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
*/

#include <iostream>

#include <raylib.h>
#include <imgui.h>
#include <spdlog/spdlog.h>

#include "utils/argparser.hpp"
#include "utils/spdlog_formatters.hpp"
#include "rlImGui/rlImGui.hpp"
#include "logic/game_of_life.hpp"
#include "graphics/cell.hpp"
#include "graphics/cell_board.hpp"

constexpr int DEFAULT_SCREEN_WIDTH{800};
constexpr int DEFAULT_SCREEN_HEIGHT{600};
constexpr char const* const WINDOW_TITLE = "Game of Life";

void setup_logging(bool debug_enabled) {
  if (debug_enabled) {
    spdlog::set_level(spdlog::level::debug);
  } else {
    spdlog::set_level(spdlog::level::info);
  }

  spdlog::info("Logging enabled!");
  spdlog::debug("Debug enabled!");
}

void log_program_arguments(Argparser const& args) {
  spdlog::debug("Program exec: {}", args.executable());
  spdlog::debug("Program arguments: {}", args);
}

void draw_gui() {
  ImGui::Begin("Settings and informations");
  ImGui::Text("Hello there!");
  ImGui::End();
}

int main(int argc, char** argv) {
  using namespace std::chrono_literals;
  auto const arguments = Argparser(argc, argv);

  setup_logging(arguments.exists("--debug-log-enabled"));
  log_program_arguments(arguments);

  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);
  SetupRLImGui(true);

  auto cell = Cell();
  cell.setHeight(10);
  cell.setWidth(10);
  cell.setFillColor(GREEN);
  cell.setBorderColor(RED);
  cell.setBorderThickness(2);

  auto game = GameOfLife();
  game.setCellFieldSize(200, 200);
  game.restart();
  game.populateField([](unsigned x, unsigned y) -> CellState {
    return GetRandomValue(1, 100) < 70 ? CellState::DEAD : CellState::ALIVE;
  });

  auto board = CellBoard();
  board.setCellBase(cell);
  board.setCellField(&game.cellField());
  board.setCellSpacing(1);

  auto camera = Camera2D{};
  camera.target = {
      static_cast<float>(board.getWidth()) / 2.f,
      static_cast<float>(board.getHeight()) / 2.f
  };
  camera.offset = {
      static_cast<float>(DEFAULT_SCREEN_WIDTH) / 2.f,
      static_cast<float>(DEFAULT_SCREEN_HEIGHT) / 2.f
  };
  camera.rotation = 0.f;
  camera.zoom = 1.f;

  while (!WindowShouldClose()) {
    // Drawing
    BeginDrawing();

    ClearBackground(GRAY);

    BeginMode2D(camera);
    board.draw();
    EndMode2D();

//    BeginRLImGui();
//    draw_gui();
//    EndRLImGui();

    EndDrawing();

    // Logic
    game.step();

    if (IsKeyDown(KEY_D)) {
      camera.target.x += static_cast<float>(cell.getWidth());
    } else if (IsKeyDown(KEY_A)) {
      camera.target.x -= static_cast<float>(cell.getWidth());
    }

    if (IsKeyDown(KEY_W)) {
      camera.target.y -= static_cast<float>(cell.getHeight());
    } else if (IsKeyDown(KEY_S)) {
      camera.target.y += static_cast<float>(cell.getHeight());
    }

    camera.zoom += static_cast<float>(GetMouseWheelMove() * 0.05f);

    if (camera.zoom > 5.0f) { camera.zoom = 5.0f; }
    if (camera.zoom < 0.001f) { camera.zoom = 0.001f; }

    if (IsKeyPressed(KEY_R)) {
      camera.zoom = 1.f;
    }
  }

  ShutdownRLImGui();
  CloseWindow();
}
