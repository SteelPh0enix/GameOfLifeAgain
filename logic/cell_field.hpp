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

#include "../utils/list2d.hpp"
#include <functional>

enum class CellState {
  INVALID, DEAD, ALIVE
};

class CellField {
public:
  using CellList = List2D<CellState>;
  // StepCallback is called for each cell.
  // Arguments: list of cells, (x, y) coordinates of cell
  // Should return: State of the (x, y) cell
  using StepCallback = std::function<CellState(CellField const& cells, unsigned x, unsigned y)>;
  // PopulateCallback is used to populate the list of cells
  // Similar to StepCallback, it's called for each cell
  // Arguments: (x, y) coordinates of current cell
  // Should return: State of (x, y) cell
  using PopulateCallback = std::function<CellState(unsigned x, unsigned y)>;

  CellField() = default;
  CellField(unsigned width, unsigned height);

  [[nodiscard]] unsigned height() const;
  [[nodiscard]] unsigned width() const;

  void resize(unsigned width, unsigned height, bool clear = true);
  [[nodiscard]] CellState get(unsigned x, unsigned y) const;

  void populate(PopulateCallback const& populateFunc);
  void setStepCallback(const StepCallback& callback);

  void step();
  void clear();

  [[nodiscard]] bool pointInBounds(unsigned x, unsigned y) const;
  [[nodiscard]] unsigned neightbourCellsCount(unsigned x, unsigned y, CellState state = CellState::ALIVE) const;

private:
  unsigned _width{};
  unsigned _height{};
  CellList _cell_list{};
  StepCallback _step_callback{};
};

