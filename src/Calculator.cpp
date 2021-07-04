#include "Calculator.hpp"

#include <iostream>

int Calculator::OperatorPriority(const std::string &ch) {
  if (ch == "+" || ch == "-") {
    return 1; //Precedence of + or - is 1
  } else if (ch == "*" || ch == "/") {
    return 2; //Precedence of * or / is 2
  } else if (ch == "^") {
    return 3; //Precedence of ^ is 3
  } else {
    return 0;
  }
}

bool Calculator::IsNumber(const std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

Result<std::vector<Token>> Calculator::InfixToPostfix(const std::vector<Token> &infix) {
  Result<std::vector<Token>> result;
  std::vector<Token> postfix;
  std::stack<Token> stack;

  for (const auto &it: infix) {
    if (it.token_type == TokenType::CONSTANT) {
      postfix.emplace_back(it);
      continue;
    }

    if (it.token == "(") {
      stack.push(it);
      continue;
    }

    if (it.token == ")") {
      while (!stack.empty() && stack.top().token != "(") {
        postfix.emplace_back(stack.top());
        stack.pop();
      }

      if (stack.empty()) {
        result.SetError("wrong input data/calculation error");
        return result;
      }

      stack.pop();
      continue;
    }

    if (it.token_type == TokenType::OPERATOR) {
      if (stack.empty() ||
          OperatorPriority(it.token) > OperatorPriority(stack.top().token)) {
        stack.push(it);
      } else {
        while (!stack.empty() &&
            OperatorPriority(it.token) <= OperatorPriority(stack.top().token)) {
          postfix.emplace_back(stack.top());
          stack.pop();
        }
        stack.push(it);
      };
    }
  }

  while (!stack.empty()) {
    Token top = stack.top();
    if (top.token != "(") {
      postfix.emplace_back(top);
    }
    stack.pop();
  }
  result.SetValue(std::move(postfix));
  return result;
}

std::vector<Token> Calculator::PrepareInfixString(const std::string &input) {
  std::string result;
  std::string input1;

  for (const auto &it: input) {
    if (' ' == it) {
      continue;
    }
    input1.push_back(it);
  }

  std::string input2;

  auto it = input1.begin();
  while (it != input1.end()) {
    size_t i = it - input1.begin();
    if (0 == i && '-' == *it) {
      input2 += "0-";
      ++it;
      continue;
    }

    if (i >= 1 && '-' == *it && '(' == *(it - 1)) {
      input2 += "0-";
      ++it;
      continue;
    }
    input2 += *it;
    ++it;
  }

  std::vector<Token> tokens;
  std::stack<Token> stack;
  std::string buff;
  for (auto it1: input2) {
    if (IsNumber(std::string{it1}) || isalpha(it1)) {
      buff += it1;
    }
    if ('+' == it1 ||
        '*' == it1 ||
        '-' == it1 ||
        '/' == it1 ||
        ')' == it1 ||
        '(' == it1
        ) {
      if (!buff.empty()) {
        tokens.emplace_back(Token{TokenType::CONSTANT, buff});
        buff = "";
      }
    }

    if ('+' == it1 ||
        '*' == it1 ||
        '/' == it1 ||
        '-' == it1) {
      tokens.emplace_back(Token{TokenType::OPERATOR,
                                std::string{it1}});
    }

    if ('(' == it1 || ')' == it1) {
      tokens.emplace_back(Token{TokenType::PARENTHESES,
                                std::string{it1}});
    }

  }
  if (!buff.empty()) {
    tokens.emplace_back(Token{TokenType::CONSTANT, buff});
    buff = "";
  }

  return tokens;

}

Result<int64_t> Calculator::CalculateResult(const std::string &input) {
  Result<int64_t> result;
  auto prep = PrepareInfixString(input);
  auto inf2post_result = InfixToPostfix(prep);
  if (inf2post_result.HasError()) {
    result.SetError(inf2post_result.ErrorDesc());
    return result;
  }
  auto inf2post = inf2post_result.GetValue();

  std::stack<int64_t> stack;
  for (const auto &it: inf2post) {
    if (it.token_type == TokenType::CONSTANT) {
      stack.push(std::stoll(it.token));
    }
    if (it.token_type == TokenType::OPERATOR) {
      int64_t op1;
      int64_t op2;
      for (size_t i = 0; i < 2; ++i) {
        if (!stack.empty()) {
          if (i == 0) {
            op2 = stack.top();
          }

          if (i == 1) {
            op1 = stack.top();
          }

          stack.pop();
        } else {
          result.SetError("wrong input data/calculation error");
          return result;
        }
      }

      int64_t res;
      if (it.token == "+") {
        res = op1 + op2;
      } else if (it.token == "-") {
        res = op1 - op2;
      } else if (it.token == "*") {
        res = op1 * op2;
      } else if (it.token == "/") {
        if (op2 == 0) {
          result.SetError("zero division");
          return result;
        }
        res = op1 / op2;
      }

      stack.push(res);
    }
  }
  // assert stack.size == 1
  if (stack.size() != 1) {
    result.SetError("wrong input data/calculation error");
    return result;
  }
  result.SetValue(stack.top());
  return result;
}


