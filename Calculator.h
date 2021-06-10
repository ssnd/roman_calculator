#pragma once

#include <string>
#include <vector>
#include <stack>
#include <iostream>

#include "Result.h"

enum class TokenType {
  OPERATOR,
  PARENTHESES,
  CONSTANT,
};

struct Token {
  TokenType token_type;
  std::string token;
};

class Calculator {
  static bool AddCatchOverflow(int64_t *result, int64_t a, int64_t b) {
    *result = a + b;
    if (a > 0 && b > 0 && *result < 0)
      return true;
    if (a < 0 && b < 0 && *result > 0)
      return true;
    return false;
  }
  static bool MultiplyCatchOverflow(int64_t *result, int64_t a, int64_t b) {
    *result = a * b;
    if (a > 0 && b > 0 && *result < 0)
      return true;
    if (a < 0 && b < 0 && *result < 0)
      return true;
    if (a > 0 && b < 0 && *result > 0)
      return true;
    if (a < 0 && b > 0 && *result < 0)
      return true;

    return false;
  }

  static int OperatorPriority(const std::string &ch);
  static bool IsNumber(const std::string &s);
  static Result<std::vector<Token>> InfixToPostfix(const std::vector<Token> &infix);
  static std::vector<Token> PrepareInfixString(const std::string &input);
 public:
  static Result<int64_t> CalculateResult(const std::string &input);
};