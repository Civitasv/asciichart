#ifndef INCLUDE_ASCII_COLOR_H_
#define INCLUDE_ASCII_COLOR_H_
#include <string>

namespace COLOR
{
    std::string BLACK = "\x1b[30m";
    std::string RED = "\x1b[31m";
    std::string GREEN = "\x1b[32m";
    std::string YELLOW = "\x1b[33m";
    std::string BLUE = "\x1b[34m";
    std::string MAGENTA = "\x1b[35m";
    std::string CYAN = "\x1b[36m";
    std::string LIGHTGRAY = "\x1b[37m";
    std::string DEFAULT = "\x1b[39m";
    std::string DARKGRAY = "\x1b[90m";
    std::string LIGHTRED = "\x1b[91m";
    std::string LIGHTGREEN = "\x1b[92m";
    std::string LIGHTYELLOW = "\x1b[93m";
    std::string LIGHTBLUE = "\x1b[94m";
    std::string LIGHTMAGENTA = "\x1b[95m";
    std::string LIGHTCYAN = "\x1b[96m";
    std::string WHITE = "\x1b[97m";
    std::string RESET = "\x1b[0m";
}
#endif