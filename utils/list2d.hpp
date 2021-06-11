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
#include <vector>
#include <algorithm>
#include <utility>

// Usage requirements: T must be default-constructible
template <typename T>
class List2D {
public:
  using Type = T;
  using Container = std::vector<Type>;
  using Iterator = typename Container::iterator;
  using ConstIterator = typename Container::const_iterator;
  using PointPair = std::pair<unsigned, unsigned>;

  List2D() = default;
  List2D(unsigned width, unsigned height) {
    resize(width, height);
  }

  void resize(unsigned width, unsigned height) {
    _width = width;
    _height = height;
    _data.resize(_width*_height);
  }

  [[nodiscard]] unsigned width() const {
    return _width;
  }

  [[nodiscard]] unsigned height() const {
    return _height;
  }

  Type& get(unsigned x, unsigned y) {
    return _data.at(XYToIndex(x, y));
  }

  Type const& get(unsigned x, unsigned y) const {
    return _data.at(XYToIndex(x, y));
  }

  Type operator[](PointPair const& coordinates) const {
    return _data[XYToIndex(coordinates.first, coordinates.second)];
  }

  void set(unsigned x, unsigned y, Type const& value) {
    _data.at(XYToIndex(x, y)) = value;
  }

  Iterator begin() {
    return _data.begin();
  }

  Iterator end() {
    return _data.end();
  }

  ConstIterator begin() const {
    return _data.begin();
  }

  ConstIterator end() const {
    return _data.end();
  }

  void clear() {
    std::fill(begin(), end(), Type{});
  }

  void fill(Type const& value) {
    std::fill(begin(), end(), value);
  }

private:
  // Assuming that (0, 0) is bottom-left corner
  [[nodiscard]] unsigned XYToIndex(unsigned x, unsigned y) const {
    return (y*_width)+x;
  }

  unsigned _width{};
  unsigned _height{};
  Container _data{};
};

