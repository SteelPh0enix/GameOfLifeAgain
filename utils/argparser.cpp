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

#include "argparser.hpp"
#include <algorithm>

Argparser::Argparser(int argc, char** argv) {
  _exec = std::string(argv[0]);
  if (argc > 1) {
    _args.resize(argc - 1);
    for (int i = 1; i < argc; i++) {
      _args[i-1] = std::string(argv[i]);
    }
  }
}

Argparser::Arglist::size_type Argparser::arguments_amount() const {
  return _args.size();
}

bool Argparser::exists(const std::string& arg) const {
  return std::find(begin(), end(), arg) != end();
}

std::string const& Argparser::operator[](unsigned int i) const {
  return _args.at(i);
}

std::string Argparser::executable() const {
  return _exec;
}

Argparser::Arglist::const_iterator Argparser::end() const {
  return _args.end();
}

Argparser::Arglist::const_iterator Argparser::begin() const {
  return _args.begin();
}
