#include <cmath>
#include <iostream>
#include <vector>

#include "ascii/ascii.h"

int main()
{
  setlocale(LC_ALL, "");

  std::vector<double> series;
  for (int i = 0; i < 200; i += 2)
  {
    series.push_back(15 * std::cos(i * (kPI * 8) / 120));
  }

  std::vector<double> series2;
  for (int i = 0; i < 200; i += 2)
  {
    series2.push_back(15 * std::sin(i * ((kPI * 4) / 100)));
  }
  Asciichart asciichart(std::vector<std::vector<double>>{series, series2});
  std::wcout << '\n'
             << asciichart.height(6).Plot() << '\n';
  return 0;
}