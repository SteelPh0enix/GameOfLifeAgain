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

#include "../logic/game_of_life.hpp"
#include "argparser.hpp"

#include <spdlog/fmt/fmt.h>
#include <sstream>
#include <string>

template<>
struct fmt::formatter<GameOfLife::Rules> {
  auto constexpr parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
    auto it = ctx.begin();
    auto const end = ctx.end();

    if (it != end && *it != '}') {
      throw format_error("Invalid format");
    }

    return it;
  }

  template <typename FormatContext>
  auto format(GameOfLife::Rules const& rules, FormatContext& ctx) -> decltype(ctx.out()) {
    std::stringstream format_stream{};
    for(auto const r: rules.survive) {
      format_stream << r;
    }
    format_stream << '/';
    for(auto const r: rules.revive) {
      format_stream << r;
    }

    return format_to(ctx.out(), format_stream.str());
  }
};

template<>
struct fmt::formatter<Argparser> {
  auto constexpr parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
    auto it = ctx.begin();
    auto const end = ctx.end();

    if (it != end && *it != '}') {
      throw format_error("Invalid format");
    }

    return it;
  }

  template <typename FormatContext>
  auto format(Argparser const& argparser, FormatContext& ctx) -> decltype(ctx.out()) {
    std::stringstream format_stream{};

    if (argparser.arguments_amount() > 0) {
      format_stream << "[";
      for (auto it = argparser.begin(); it != argparser.end() - 1; it++) {
        format_stream << *it << ", ";
      }
      format_stream << *(argparser.end() - 1) << "]";
    } else {
      format_stream << "None";
    }

    return format_to(ctx.out(), format_stream.str());
  }
};
