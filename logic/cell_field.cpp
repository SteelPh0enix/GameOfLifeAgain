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

#include "cell_field.hpp"
#include <spdlog/spdlog.h>

CellField::CellField(unsigned int width, unsigned int height) {
  resize(width, height);
}

void CellField::resize(unsigned int width, unsigned int height, bool clear) {
  _width = width;
  _height = height;
  _cell_list.resize(_width, _height);
  if (clear) {
    this->clear();
  }
}

CellState CellField::get(unsigned int x, unsigned int y) const {
  return _cell_list.get(x, y);
}

void CellField::populate(PopulateCallback const& populateFunc) {
  for (unsigned y = 0; y < height(); y++) {
    for (unsigned x = 0; x < width(); x++) {
      _cell_list.set(x, y, populateFunc(x, y));
    }
  }
}

void CellField::setStepCallback(StepCallback const& callback) {
  _step_callback = callback;
}

void CellField::step() {
  auto const workingCellField = *this;
  for (unsigned y = 0; y < height(); y++) {
    for (unsigned x = 0; x < width(); x++) {
      _cell_list.set(x, y, _step_callback(workingCellField, x, y));
    }
  }
}

unsigned CellField::height() const {
  return _height;
}

unsigned CellField::width() const {
  return _width;
}

void CellField::clear() {
  _cell_list.fill(CellState::DEAD);
}

unsigned CellField::neightbourCellsCount(unsigned int x, unsigned int y, CellState state) const {
  auto const intX = static_cast<int>(x);
  auto const intY = static_cast<int>(y);
  unsigned cellCount{0};

  for (int dy = intY - 1; dy <= intY + 1; dy++) {
    for (int dx = intX - 1; dx <= intX + 1; dx++) {
      auto const pointCorrect = pointInBounds(dx, dy);
      auto const pointIsOrigin = (dx == intX && dy == intY);
      if (pointCorrect && !pointIsOrigin) {
        auto const currentCellState = _cell_list[{dx, dy}];
        if (currentCellState == state) {
          cellCount++;
        }
      }
    }
  }

  return cellCount;
}

bool CellField::pointInBounds(unsigned int x, unsigned int y) const {
  return (x < width() && y < height());
}
