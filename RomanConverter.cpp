#include "RomanConverter.h"

#include <iostream>

std::string RomanConverter::MinusDigit(char one, char five, char ten, int64_t x) {
  if (x <= 3) {
    return std::string().assign(x, one);
  }
  if (x <= 5) {
    return std::string().assign(5 - x, one) + five;
  }
  if (x <= 8) {
    return five + std::string().assign(x - 5, one);
  }
  return std::string().assign(10 - x, one) + ten;
}

std::string RomanConverter::DecimalToRoman(int64_t x) {
  assert(x >= 0);
  assert (x<=1000000000);
  if (x == 0) {
    return "Z";
  }

  if (x >= 1000) {
    return x - 1000 > 0 ? "M" + DecimalToRoman(x - 1000) : "M";
  }

  if (x >= 100) {
    std::string d = MinusDigit('C', 'D', 'M', x / 100);
    return x % 100 > 0 ? d + DecimalToRoman(x % 100) : d;
  }

  if (x >= 10) {
    std::string d = MinusDigit('X', 'L', 'C', x / 10);
    return x % 10 > 0 ? d + DecimalToRoman(x % 10) : d;
  }

  return MinusDigit('I', 'V', 'X', x);
}

int64_t RomanConverter::RomanValue(char r) {
  switch (r) {
    case 'Z':return 0;
    case 'I':return 1;
    case 'V':return 5;
    case 'X':return 10;
    case 'L':return 50;
    case 'C':return 100;
    case 'D':return 500;
    case 'M':return 1000;
    default: return -1;
  }

}

int64_t RomanConverter::RomanToDecimal(const std::string &input) {
  int64_t result = 0;
  for (size_t i = 0; i < input.size(); ++i) {
    int current_value = RomanValue(input[i]);

    if (i + 1 < input.size()) {
      int64_t next_value = RomanValue(input[i + 1]);
      if (current_value >= next_value) {
        result = result + current_value;
      } else {
        result = result + next_value - current_value;
        ++i;
      }

    } else {
      result += current_value;
    }

  }

  return result;
}
