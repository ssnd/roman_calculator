#include <iostream>

#include "RomanConverter.hpp"


std::string RomanConverter::DecimalToRoman(int64_t value) {
  struct roman_t { unsigned int value; char const *numeral; };
  roman_t roman_map[] =
      {
          {1000, "M"}, {900, "CM"},
          {500, "D"}, {400, "CD"},
          {100, "C"}, {90, "XC"},
          {50, "L"}, {40, "XL"},
          {10, "X"}, {9, "IX"},
          {5, "V"}, {4, "IV"},
          {1, "I"},
          {0, NULL} // end marker
      };

  std::string result;
  for (roman_t *current = roman_map; current->value > 0; ++current) {
    while (value >= current->value) {
      result += current->numeral;
      value -= current->value;
    }
  }

  return result;
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
