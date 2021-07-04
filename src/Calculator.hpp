#pragma once

#include <string>
#include <vector>
#include <stack>
#include <iostream>

#include "Result.hpp"


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
 private:
  static int OperatorPriority(const std::string &ch);
  static bool IsNumber(const std::string &s);
  static Result<std::vector<Token>> InfixToPostfix(const std::vector<Token> &infix);
  static std::vector<Token> PrepareInfixString(const std::string &input);
  
 public:
  static Result<int64_t> CalculateResult(const std::string &input);
};