#ifndef INCLUDE_ASCII_TEXT_H_
#define INCLUDE_ASCII_TEXT_H_
#include "style.h"

namespace ascii {
class Text {
public:
  Text() {}
  Text(std::string text) : text_(text) {}
  Text(std::string text, Style style) : text_(text), style_(style) {}

  Text &style(Style style) {
    style_ = style;
    return *this;
  }

  Text &text(std::string text) {
    text_ = text;
    return *this;
  }

  std::string text() { return text_; }

  friend std::ostream &operator<<(std::ostream &os, const Text &val) {
    os << val.style_ << val.text_ << Decoration::From(Decoration::RESET);
    return os;
  }

private:
  std::string text_;
  Style style_;
};
} // namespace ascii
#endif // !INCLUDE_ASCII_TEXT_H_
