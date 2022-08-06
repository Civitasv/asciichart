#ifndef INCLUDE_ASCII_COLOR_H_
#define INCLUDE_ASCII_COLOR_H_
#include <string>

namespace ascii {
class Color {
public:
  inline static const std::string BLACK = "\x1b[30m";
  inline static const std::string RED = "\x1b[31m";
  inline static const std::string GREEN = "\x1b[32m";
  inline static const std::string YELLOW = "\x1b[33m";
  inline static const std::string BLUE = "\x1b[34m";
  inline static const std::string MAGENTA = "\x1b[35m";
  inline static const std::string CYAN = "\x1b[36m";
  inline static const std::string LIGHTGRAY = "\x1b[37m";
  inline static const std::string DEFAULT = "\x1b[39m";
  inline static const std::string DARKGRAY = "\x1b[90m";
  inline static const std::string LIGHTRED = "\x1b[91m";
  inline static const std::string LIGHTGREEN = "\x1b[92m";
  inline static const std::string LIGHTYELLOW = "\x1b[93m";
  inline static const std::string LIGHTBLUE = "\x1b[94m";
  inline static const std::string LIGHTMAGENTA = "\x1b[95m";
  inline static const std::string LIGHTCYAN = "\x1b[96m";
  inline static const std::string WHITE = "\x1b[97m";
  inline static const std::string RESET = "\x1b[0m";
};
} // namespace ascii
#endif