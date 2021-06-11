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

#include "cell_board.hpp"

int CellBoard::getWidth() const {
  if (_field != nullptr) {
    auto const cells_amount = static_cast<int>(_field->width());
    return cells_amount * (_cellBase.getWidth() + (_spacing * 2));
  }
  return 0;
}

int CellBoard::getHeight() const {
  if (_field != nullptr) {
    auto const cells_amount = static_cast<int>(_field->height());
    return cells_amount * (_cellBase.getHeight() + (_spacing * 2));
  }
  return 0;
}

Cell const& CellBoard::getCellBase() const {
  return _cellBase;
}

void CellBoard::setCellBase(Cell cell) {
  _cellBase = cell;
}

void CellBoard::draw() const {
  for (int y = 0; y < _field->height(); y++) {
    for (int x = 0; x < _field->width(); x++) {
      // check if the cell is supposed to be drawn
      if (_field->get(x, y) == CellState::ALIVE) {

        // calculate X and Y of the cell, origin is top-left
        int const cellX = ((x + 1) * _spacing) + (x * _cellBase.getWidth());
        int const cellY = ((y + 1) * _spacing) + (y * _cellBase.getHeight());

        // draw the cell
        _cellBase.draw(cellX, cellY);
      }
    }
  }
}

CellField const* CellBoard::getCellField() const {
  return _field;
}

void CellBoard::setCellField(const CellField* cellField) {
  _field = cellField;
}

void CellBoard::setCellSpacing(int spacingPixels) {
  _spacing = spacingPixels;
}

int CellBoard::getSpacing() const {
  return _spacing;
}
