#ifndef INCLUDE_ASCII_ASCII_H_
#define INCLUDE_ASCII_ASCII_H_

#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <codecvt>

#include "color.h"
#include "constants.h"

class Asciichart
{
public:
  explicit Asciichart(std::vector<double> series)
      : _height(kDoubleNotANumber),
        _min(kDoubleInfinity),
        _max(kDoubleNegInfinity),
        _offset(3)
  {
    InitSeries(series);
    InitColors();
    InitSymbols();
  }

  explicit Asciichart(std::vector<std::vector<double>> series)
      : _height(kDoubleNotANumber),
        _min(kDoubleInfinity),
        _max(kDoubleNegInfinity),
        _offset(3)
  {
    InitSeries(series);
    InitColors();
    InitSymbols();
  }

  /// Set height of chart.
  Asciichart &height(double height)
  {
    _height = height;
    return *this;
  }

  /// Set colors of chart.
  Asciichart &colors(std::vector<std::string> colors)
  {
    _colors = colors;
    return *this;
  }

  /// Set min of chart.
  /// This value will be override if larger than true min value.
  Asciichart &min(double min)
  {
    _min = min;
    return *this;
  }

  /// Set max of chart.
  /// This value will be override if less than true max value.
  Asciichart &max(double max)
  {
    _max = max;
    return *this;
  }

  /// Set offset of label.
  Asciichart &offset(size_t offset)
  {
    _offset = offset;
    return *this;
  }

  /// Set symbols used to plot.
  Asciichart &symbols(std::map<std::string, std::wstring> symbols)
  {
    _symbols = symbols;
    return *this;
  }

  /// Generate this chart.
  std::wstring Plot()
  {
    // 1. 计算最大最小值
    for (auto &line : _series)
    {
      for (auto &item : line)
      {
        _min = std::min(item, _min);
        _max = std::max(item, _max);
      }
    }

    // 2. 计算跨度
    auto range = _max - _min;

    // 3. 赋值 width 和 height
    int width = 0;
    for (auto &item : _series)
    {
      width = std::max(width, (int)item.size());
    }
    width += _offset;

    if (std::isnan(_height))
    {
      _height = range;
    }

    auto ratio = _height / range;

    int min2 = std::round(_min * ratio);
    int max2 = std::round(_max * ratio);

    // 4. 赋值 rows 和 cols
    auto rows = max2 - min2;
    auto cols = width;

    // 5. 空初始化
    std::vector<std::vector<std::wstring>> screen(rows + 1, std::vector<std::wstring>(cols, _symbols["empty"]));

    // 6. axis + labels
    for (double y = min2; y <= max2; y++)
    {
      auto label = FormatLabel(_min + (y - min2) * range / rows);
      // vertical reverse
      screen[rows - (y - min2)][0] = Colored(label, COLOR::BLACK);
      screen[rows - (y - min2)][_offset - 1] = Colored((y == 0) ? _symbols["center"] : _symbols["axis"], COLOR::CYAN);
    }

    // 7. Content
    for (size_t j = 0; j < _series.size(); j++)
    {
      auto color = _colors[j % _colors.size()];
      auto y0 = std::round(_series[j][0] * ratio) - min2;
      // vertical reverse
      screen[rows - y0][_offset - 1] = Colored(_symbols["center"], color);

      for (size_t i = 0; i < _series[j].size() - 1; i++)
      {
        auto y0 = std::round(_series[j][i] * ratio) - min2;
        auto y1 = std::round(_series[j][i + 1] * ratio) - min2;

        if (y0 == y1)
        {
          screen[rows - y0][i + _offset] = Colored(_symbols["parellel"], color);
        }
        else
        {
          screen[rows - y1][i + _offset] = Colored(y0 > y1 ? _symbols["down"] : _symbols["up"], color);
          screen[rows - y0][i + _offset] = Colored(y0 > y1 ? _symbols["ldown"] : _symbols["lup"], color);
          auto from = std::min(y0, y1);
          auto to = std::max(y0, y1);
          for (size_t y = from + 1; y < to; y++)
          {
            screen[rows - y][i + _offset] = _symbols["vertical"];
          }
        }
      }
    }
    return Print(screen);
  }

private:
  std::map<std::string, std::wstring> _symbols;
  std::vector<std::vector<double>> _series;
  std::vector<std::string> _colors;

  double _min;
  double _max;
  double _height;
  double _offset;

  void InitSeries(std::vector<double> &series)
  {
    _series.push_back(series);
  }

  void InitSeries(std::vector<std::vector<double>> &series)
  {
    _series = series;
  }

  void InitColors()
  {
    _colors = std::vector<std::string>{COLOR::BLACK, COLOR::RED, COLOR::GREEN};
  }

  void InitSymbols()
  {
    _symbols = {{"empty", L" "},
                {"center", L"┼"},
                {"axis", L"┤"},
                {"c1", L"╶"},
                {"c2", L"╴"},
                {"parellel", L"─"},
                {"down", L"╰"},
                {"up", L"╭"},
                {"ldown", L"╮"},
                {"lup", L"╯"},
                {"vertical", L"│"}};
  }

  std::wstring FormatLabel(double x)
  {
    std::wstringstream ss;
    ss << std::setw(10) << std::setfill(L' ') << std::setprecision(2);
    ss << x;
    return ss.str();
  }

  std::wstring Colored(std::wstring label, std::string color)
  {
    return String2wstring(color) + label + String2wstring(COLOR::RESET);
  }

  std::wstring String2wstring(std::string origin)
  {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(origin);
  }

  std::wstring Print(std::vector<std::vector<std::wstring>> &screen)
  {
    std::wstringstream os;
    for (auto &line : screen)
    {
      for (auto &item : line)
      {
        os << item.data();
      }
      os << L"\n";
    }
    return os.str();
  }
};
#endif