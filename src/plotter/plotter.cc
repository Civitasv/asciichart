#include <array>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <io.h>
#include <fcntl.h>
#include <vector>

#include "ascii/ascii.h"

int main()
{
  _setmode(_fileno(stdout), _O_U16TEXT);

  std::vector<double> series;
  for (int i = 0; i < 100; i++)
  {
    series.push_back(15 * std::cos(i * (kPI * 8) / 120));
  }

  std::vector<double> series2;
  for (int i = 0; i < 100; i++)
  {
    series2.push_back(15 * std::sin(i * ((kPI * 4) / 100)));
  }
  Asciichart asciichart(std::vector<std::vector<double>>{series, series2});
  std::wcout << asciichart.height(6).Plot();
  return 0;
}