#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

#include "ascii/ascii.h"

namespace {

  void example1() {
    using namespace ascii;
    std::vector<double> series;
    for (int i = 0; i < 100; i += 2) {
      series.push_back(15 * std::cos(i * (kPI * 8) / 120));
    }

    Asciichart asciichart(std::vector<std::vector<double>>{series});
    std::cout << asciichart.type(Asciichart::LINE).height(6).Plot();
  }

  void example2() {
    using namespace ascii;
    std::vector<double> series;
    std::vector<double> series2;
    for (int i = 0; i < 100; i += 2) {
      series.push_back(15 * std::cos(i * (kPI * 8) / 120));
      series2.push_back(15 * std::sin(i * ((kPI * 4) / 100)));
    }
    Asciichart asciichart(std::vector<std::vector<double>>{series, series2});
    std::cout << asciichart.type(Asciichart::LINE).height(6).Plot();
  }

  void example3() {
    using namespace ascii;
    std::vector<double> series;
    for (int i = 0; i < 100; i += 2) {
      series.push_back(3400 * std::cos(i * (kPI * 8) / 120));
    }

    Asciichart asciichart(std::vector<std::vector<double>>{series});
    std::cout << asciichart.type(Asciichart::LINE).height(6).Plot();
  }

  void animation() {
    using namespace ascii;
    std::vector<double> series;
    std::vector<double> series2;
    int height = 6;
    for (int i = 0; i < 100; i += 2) {
      series.push_back(15 * std::cos(i * (kPI * 8) / 120));
      series2.push_back(15 * std::sin(i * ((kPI * 4) / 100)));
      Asciichart asciichart(std::vector<std::vector<double>>{series, series2});
      if (i != 0) {
        for (int j = 0; j <= height; j++) {
          std::cout << "\033[A\033[2K"; // This is used for clear previous chart
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }
      std::cout << asciichart.type(Asciichart::LINE)
                       .show_legend(true)
                       .height(height)
                       .Plot();
    }
  }

  void example_legend() {
    using namespace ascii;
    std::vector<double> series;
    std::vector<double> series2;
    for (int i = 0; i < 100; i += 2) {
      series.push_back(15 * std::cos(i * (kPI * 8) / 120));
      series2.push_back(15 * std::sin(i * ((kPI * 4) / 100)));
    }
    Asciichart asciichart(std::vector<std::vector<double>>{series, series2});
    std::cout
        << asciichart.type(Asciichart::LINE).show_legend(true).height(6).Plot();
  }

  void example_legend2() {
    using namespace ascii;
    std::vector<double> series;
    std::vector<double> series2;
    for (int i = 0; i < 100; i += 2) {
      series.push_back(15 * std::cos(i * (kPI * 8) / 120));
      series2.push_back(15 * std::sin(i * ((kPI * 4) / 100)));
    }
    Asciichart asciichart({{"A", series}, {"B", series2}});
    std::cout
        << asciichart.type(Asciichart::LINE).show_legend(true).height(6).Plot();
  }

  void usage(const char* p) {
    std::cout << "usage: " << p << " [1-6]\n";
  }
}

int main(int argc, char* argv[])
{
  if (argc != 2) {
    usage(argv[0]);
    return 1;
  }

  switch (std::stol(argv[1])) {
  case 1: example1(); break;
  case 2: example2(); break;
  case 3: example3(); break;
  case 4: example_legend(); break;
  case 5: example_legend2(); break;
  case 6: animation(); break;
  default: usage(argv[0]); return 1;
  }

  return 0;
}
