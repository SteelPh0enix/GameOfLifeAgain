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

#pragma once
#include <string>
#include <vector>
#include <initializer_list>
#include "cell_field.hpp"

class GameOfLife {
public:
  struct Rules {
    std::vector<unsigned> survive{};
    std::vector<unsigned> revive{};
  };

  GameOfLife();
  // Set rules with rulestring, separated with '/'
  // Rulestring patterns is [neightbour cells to survive]/[neightbour cells to revive]
  // For example, Conway's Game of Life rulestring is "23/3"
  // Will throw std::invalid_argument on incorrect rulestring
  explicit GameOfLife(std::string const& rulestring);

  // Set rules with Rules object
  // Will throw std::invalid_argument on incorrect rulestring
  explicit GameOfLife(Rules const& rules);

  bool setRules(Rules const& rules);
  bool setRules(std::string const& rulestring);
  [[nodiscard]] Rules rules() const;

  [[nodiscard]] CellField const& cellField() const;
  void populateField(CellField::PopulateCallback const& populateFunc);
  void setCellFieldSize(unsigned x, unsigned y);

  [[nodiscard]] unsigned cellFieldWidth() const;
  [[nodiscard]] unsigned cellFieldHeight() const;

  void step();
  void restart();

private:
  static constexpr auto RULESTRING_SEPARATOR = '/';
  static Rules const DEFAULT_RULES;
  CellState stepCallback(CellField const& cells, unsigned x, unsigned y);
  void setStepCallback();

  [[nodiscard]] bool cellSurvives(unsigned aliveNeightbourCount) const;
  [[nodiscard]] bool cellRevives(unsigned aliveNeightbourCount) const;

  Rules _rules{DEFAULT_RULES};
  CellField _field{};
};

