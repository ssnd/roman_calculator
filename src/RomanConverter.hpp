#pragma once

#include <string>


class RomanConverter {
 public:
  static std::string MinusDigit(char one, char five, char ten, int64_t x);
  static std::string DecimalToRoman(int64_t x);
  static int64_t RomanToDecimal(const std::string &input);
  static int64_t RomanValue(char r);
};