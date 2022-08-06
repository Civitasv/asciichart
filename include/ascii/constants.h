#ifndef INCLUDE_ASCII_CONSTANTS_H_
#define INCLUDE_ASCII_CONSTANTS_H_

#include <limits>

namespace ascii {
constexpr double kPI = 3.14159265358979323846;
constexpr double kDoubleNotANumber = std::numeric_limits<double>::quiet_NaN();
constexpr double kDoubleInfinity = (std::numeric_limits<double>::infinity)();
constexpr double kDoubleNegInfinity =
    (-(std::numeric_limits<double>::infinity)());
} // namespace ascii
#endif