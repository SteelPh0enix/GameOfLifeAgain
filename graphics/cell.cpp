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

#include "cell.hpp"

Cell::Cell(int width, int height, int borderThickness) {
  setWidth(width);
  setHeight(height);
  setBorderThickness(borderThickness);
}

Cell::Cell(int width, int height, int borderThickness, const Color& borderColor,
           const Color& fillColor) {
  setWidth(width);
  setHeight(height);
  setBorderThickness(borderThickness);
  setBorderColor(borderColor);
  setFillColor(fillColor);
}

int Cell::getWidth() const {
  return _width;
}

int Cell::getHeight() const {
  return _height;
}

int Cell::getBorderThickness() const {
  return _border_thickness;
}

void Cell::setWidth(int width) {
  _width = width;
}

void Cell::setHeight(int height) {
  _height = height;
}

void Cell::setBorderThickness(int borderThickness) {
  _border_thickness = borderThickness;
}

const Color& Cell::getBorderColor() const {
  return _border_color;
}

void Cell::setBorderColor(const Color& borderColor) {
  _border_color = borderColor;
}

const Color& Cell::getFillColor() const {
  return _fill_color;
}

void Cell::setFillColor(const Color& fillColor) {
  _fill_color = fillColor;
}

void Cell::draw(int x, int y) const {
  DrawRectangle(x, y, getWidth(), getHeight(), getFillColor());
  DrawRectangleLinesEx(
      {static_cast<float>(x),
       static_cast<float>(y),
       static_cast<float>(getWidth()),
       static_cast<float>(getHeight())},
      getBorderThickness(), getBorderColor());
}


