#ifndef INCLUDE_ASCII_ASCII_H_
#define INCLUDE_ASCII_ASCII_H_

#include <cmath>
#include <codecvt>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "color.h"
#include "constants.h"
#include "text.h"

namespace ascii {
class Asciichart {
public:
  explicit Asciichart(std::vector<double> series)
      : height_(kDoubleNotANumber), min_(kDoubleInfinity),
        max_(kDoubleNegInfinity), offset_(3) {
    InitSeries(series);
    InitStyles();
    InitSymbols();
  }

  explicit Asciichart(std::vector<std::vector<double>> series)
      : height_(kDoubleNotANumber), min_(kDoubleInfinity),
        max_(kDoubleNegInfinity), offset_(3) {
    InitSeries(series);
    InitStyles();
    InitSymbols();
  }

  // For associating a text label with each series
  explicit Asciichart(const std::unordered_map<std::string, std::vector<double>> &series)
      : height_(kDoubleNotANumber), min_(kDoubleInfinity),
        max_(kDoubleNegInfinity), offset_(3) {
    InitSeries(series);
    InitStyles();
    InitSymbols();
  }

  /// Set height of chart.
  Asciichart &height(double height) {
    height_ = height;
    return *this;
  }

  /// Set colors of chart.
  Asciichart &styles(std::vector<Style> styles) {
    styles_ = styles;
    return *this;
  }

  /// Set min of chart.
  /// This value will be override if larger than true min value.
  Asciichart &min(double min) {
    min_ = min;
    return *this;
  }

  /// Set max of chart.
  /// This value will be override if less than true max value.
  Asciichart &max(double max) {
    max_ = max;
    return *this;
  }

  /// Set offset of label.
  Asciichart &offset(size_t offset) {
    offset_ = offset;
    return *this;
  }

  /// Set symbols used to plot.
  Asciichart &symbols(std::map<std::string, std::string> symbols) {
    symbols_ = symbols;
    return *this;
  }

  /// Generate this chart.
  std::string Plot() {
    // 1. calculate min and max
    for (auto &label_trace_pair : series_) {
      for (auto &item : label_trace_pair.second) {
        min_ = std::min(item, min_);
        max_ = std::max(item, max_);
      }
    }

    // 2. calaculate range
    auto range = max_ - min_;

    // 3. width and height
    int width = 0;
    for (auto &label_trace_pair : series_) {
      width = std::max(width, (int)label_trace_pair.second.size());
    }
    
    int legend_padding = 0;
    for (auto &label_trace_pair : series_) {
      legend_padding = std::max(legend_padding, (int)label_trace_pair.first.length());
    }

    auto offset = offset_ + legend_padding;

    width += offset;

    if (std::isnan(height_)) {
      height_ = range;
    }

    // calculate ratio using height and range
    auto ratio = height_ / range;

    int min2 = std::round(min_ * ratio);
    int max2 = std::round(max_ * ratio);

    // 4. rows and cols of this chart
    auto rows = max2 - min2;
    auto cols = width;

    // 5. initialize chart using empty str
    std::vector<std::vector<Text>> screen(
        rows + 1, std::vector<Text>(cols, symbols_["empty"]));

    // 6. axis + labels
    for (double y = min2; y <= max2; y++) {
      auto label = FormatLabel(std::round(min_ + (y - min2) * range / rows));
      // vertical reverse
      screen[rows - (y - min2)][legend_padding] =
          Text(label, Style().fg(Foreground::From(Color::BLUE)));
      screen[rows - (y - min2)][offset - 1] =
          Text((y == 0) ? symbols_["center"] : symbols_["axis"],
               Style().fg(Foreground::From(Color::CYAN)));
    }

    // 7. Legend
    // TODO:

    // 8. Content
    unsigned j = 0;
    for (auto &label_trace_pair : series_) {
      auto& trace = label_trace_pair.second;
      auto style = styles_[j++ % styles_.size()];
      auto y0 = std::round(trace[0] * ratio) - min2;
      // vertical reverse
      screen[rows - y0][offset - 1] = Text(symbols_["center"], style);

      for (size_t i = 0; i < trace.size() - 1; i++) {
        auto y0 = std::round(trace[i] * ratio) - min2;
        auto y1 = std::round(trace[i + 1] * ratio) - min2;

        if (y0 == y1) {
          screen[rows - y0][i + offset] = Text(symbols_["parellel"], style);
        } else {
          screen[rows - y1][i + offset] =
              Text(y0 > y1 ? symbols_["down"] : symbols_["up"], style);
          screen[rows - y0][i + offset] =
              Text(y0 > y1 ? symbols_["ldown"] : symbols_["lup"], style);
          auto from = std::min(y0, y1);
          auto to = std::max(y0, y1);
          for (size_t y = from + 1; y < to; y++) {
            screen[rows - y][i + offset] = Text(symbols_["vertical"], style);
          }
        }
      }
    }
    return Print(screen);
  }

private:
  std::map<std::string, std::string> symbols_;
  std::unordered_map<std::string, std::vector<double>> series_;
  std::vector<Style> styles_;

  double min_;
  double max_;
  double height_;
  double offset_;

  void InitSeries(std::vector<double> &series) { series_["series 0"] = series; }

  void InitSeries(std::vector<std::vector<double>> &series) {
    unsigned n = 0;
    for (const auto& s : series)
    {
      series_["series " + std::to_string(n++)] = s;
    }
  }

  void InitSeries(const std::unordered_map<std::string, std::vector<double>> &series) {
    series_ = series;
  }

  void InitStyles() {
    styles_ = {Style().fg(Foreground::From(Color::RED)),
               Style().fg(Foreground::From(Color::CYAN))};
  }

  void InitSymbols() {
    symbols_ = {{"empty", " "}, {"center", "┼"},  {"axis", "┤"},
                {"c1", "╶"},    {"c2", "╴"},      {"parellel", "─"},
                {"down", "╰"},  {"up", "╭"},      {"ldown", "╮"},
                {"lup", "╯"},   {"vertical", "│"}};
  }

  std::string FormatLabel(double x) {
    std::stringstream ss;
    ss << std::setw(10) << std::setfill(' ') << std::setprecision(2);
    ss << x;
    return ss.str();
  }

  std::string Print(std::vector<std::vector<Text>> &screen) {
    std::stringstream os;
    for (auto &line : screen) {
      for (auto &item : line) {
        os << item;
      }
      os << "\n";
    }
    return os.str();
  }
};
} // namespace ascii
#endif
