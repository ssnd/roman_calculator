#include <iostream>
#include <algorithm>

#include <string>
#include <stdlib.h>
#include "RomanConverter.hpp"
#include "Calculator.hpp"
#include "Result.hpp"

template<typename T>
T sgn(T x) {
  if (x == 0) {
    return 1;
  }

  return x / abs(x);
}

Result<std::string> ExpressionToDecimal(const std::string &input) {
  std::string buff;
  std::string result;
  Result<std::string> final_result;
  for (const auto &it: input) {
    if (it == 'I' ||
        it == 'V' ||
        it == 'X' ||
        it == 'L' ||
        it == 'C' ||
        it == 'D' ||
        it == 'M' ||
        it == 'Z') {
      buff += it;
    } else if (
        it == '+' ||
            it == '-' ||
            it == '*' ||
            it == '/' ||
            it == ')' ||
            it == '('
        ) {
      if (!buff.empty()) {
        result += std::to_string(RomanConverter::RomanToDecimal(buff));
        buff = "";
      }
      result += it;
    } else {
      final_result.SetError("wrong input data/calculation error");
      return final_result;
    };
  }

  if (!buff.empty()) {
    result += std::to_string(RomanConverter::RomanToDecimal(buff));
    buff = "";
  }
  final_result.SetValue(std::move(result));
  return final_result;
}

void CalculateResult(const std::string &input) {
  auto expr_with_decimals = ExpressionToDecimal(input);
  if (expr_with_decimals.HasError()) {
    std::cout << "error: " << expr_with_decimals.ErrorDesc() << std::endl;
    return;
  }
  auto result = Calculator::CalculateResult(expr_with_decimals.GetValue());
  if (result.HasError()) {
    std::cout << "error: " << result.ErrorDesc() << std::endl;
    return;
  }
  // no errors
  std::cout << (sgn(result.GetValue()) == -1 ? "-" : "");
  std::cout << RomanConverter::DecimalToRoman(abs(result.GetValue())) << std::endl;

}
int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    CalculateResult(line);
  }
  return 0;
}
