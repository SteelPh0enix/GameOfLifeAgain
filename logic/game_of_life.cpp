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

#include "game_of_life.hpp"
#include <stdexcept>

#include <spdlog/spdlog.h>
#include "../utils/spdlog_formatters.hpp"

GameOfLife::Rules const GameOfLife::DEFAULT_RULES{
    {2, 3},
    {3}
};

GameOfLife::GameOfLife(const std::string& rulestring) {
  setStepCallback();
  if (!setRules(rulestring)) {
    throw std::invalid_argument("Invalid rulestring passed to GameOfLife constructor!");
  }

  spdlog::debug("Created new GameOfLife object with rulestring {}", rulestring);
}

GameOfLife::GameOfLife(const GameOfLife::Rules& rules) {
  setStepCallback();
  if (!setRules(rules)) {
    throw std::invalid_argument("Invalid rules passed to GameOfLife constructor!");
  }

  spdlog::debug("Created new GameOfLife object with rules {}", this->rules());
}

bool GameOfLife::setRules(const GameOfLife::Rules& rules) {
  // Check if rules are correct
  if (rules.revive.empty() && rules.survive.empty()) {
    return false;
  }

  // Set the rules
  _rules = rules;
  spdlog::debug("Rules set to {}", this->rules());
  return true;
}

bool GameOfLife::setRules(const std::string& rulestring) {
  Rules rules{};
  spdlog::debug("Trying to create rules out of rulestring {}", rulestring);

  // Check for delimiter character, exit if there's none
  auto separator_it = std::find(rulestring.begin(), rulestring.end(), RULESTRING_SEPARATOR);
  if (separator_it == rulestring.end()) {
    return false;
  }

  // Extract the rules and filter out invalid chars
  for (auto survive_it = rulestring.begin(); survive_it != separator_it; survive_it++) {
    auto const rule_int = static_cast<unsigned>(*survive_it - '0');
    if (rule_int <= 9) {
      rules.survive.push_back(rule_int);
    }
  }

  for (auto revive_it = separator_it + 1; revive_it != rulestring.end(); revive_it++) {
    auto const rule_int = static_cast<unsigned>(*revive_it - '0');
    if (rule_int <= 9) {
      rules.revive.push_back(rule_int);
    }
  }

  // Set it via correct function, in case the rules after filtration are empty, it'll return false
  return setRules(rules);
}

GameOfLife::Rules GameOfLife::rules() const {
  return _rules;
}

CellField const& GameOfLife::cellField() const {
  return _field;
}

void GameOfLife::populateField(const CellField::PopulateCallback& populateFunc) {
  _field.populate(populateFunc);
}

void GameOfLife::setCellFieldSize(unsigned int x, unsigned int y) {
  _field.resize(x, y);
}

unsigned GameOfLife::cellFieldWidth() const {
  return _field.width();
}

unsigned GameOfLife::cellFieldHeight() const {
  return _field.height();
}

void GameOfLife::step() {
  _field.step();
}

void GameOfLife::restart() {
  _field.clear();
}

CellState GameOfLife::stepCallback(const CellField& cells, unsigned int x, unsigned int y) {
  auto const aliveNeighboursCount = cells.neightbourCellsCount(x, y, CellState::ALIVE);
  auto const currentCellState = cells.get(x, y);

  auto newCellState = currentCellState;

  if (currentCellState == CellState::DEAD) {
    auto const shouldCellRevive = cellRevives(aliveNeighboursCount);
    if (shouldCellRevive) {
      newCellState = CellState::ALIVE;
    }
  } else {
    auto const shouldCellDie = !cellSurvives(aliveNeighboursCount);
    if (shouldCellDie) {
      newCellState = CellState::DEAD;
    }
  }

  return newCellState;
}

GameOfLife::GameOfLife() {
  setStepCallback();
  spdlog::debug("Created new GameOfLife object with default rules: {}", rules());
}

bool GameOfLife::cellSurvives(unsigned int aliveNeighbourCount) const {
  return std::find(_rules.survive.begin(), _rules.survive.end(), aliveNeighbourCount) != _rules.survive.end();
}

bool GameOfLife::cellRevives(unsigned int aliveNeighbourCount) const {
  return std::find(_rules.revive.begin(), _rules.revive.end(), aliveNeighbourCount) != _rules.revive.end();
}

void GameOfLife::setStepCallback() {
  _field.setStepCallback([this](CellField const& cells, unsigned x, unsigned y) -> CellState {
    return this->stepCallback(cells, x, y);
  });
}
