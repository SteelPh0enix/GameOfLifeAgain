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
#include <raylib.h>

class Cell {
public:
  Cell() = default;
  Cell(int width, int height, int borderThickness);
  Cell(int width, int height, int borderThickness, Color const& borderColor, Color const& fillColor);

  [[nodiscard]] int getWidth() const;
  [[nodiscard]] int getHeight() const;
  [[nodiscard]] int getBorderThickness() const;
  [[nodiscard]] const Color& getBorderColor() const;
  [[nodiscard]] const Color& getFillColor() const;

  void setWidth(int width);
  void setHeight(int height);
  void setBorderThickness(int borderThickness);
  void setBorderColor(const Color& borderColor);
  void setFillColor(const Color& fillColor);

  void draw(int x, int y) const;

private:
  int _height{};
  int _width{};
  int _border_thickness{};
  Color _border_color{};
  Color _fill_color{};
};


