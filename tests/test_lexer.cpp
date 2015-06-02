#include <iostream>
#include <string>

#include "gtest/gtest.h"

#include "lexer.hpp"

using namespace kaleidoscope;


template<typename T, typename V>
void check_token(lexer::Lexer* lexer, token::Type type, V value) {
  auto tok = static_cast<T>(lexer->GetNextToken());
  EXPECT_EQ(tok->type, type);
  EXPECT_EQ(tok->value, value);
}

TEST(Lexer, Identifier) {
  const auto input = new std::istringstream{"var"};
  auto lexer = lexer::Lexer(input);

  check_token<token::Identifier*, std::string>(&lexer, token::Type::kIdentifier, "var");
}

TEST(Lexer, NumberInt) {
  const auto input = new std::istringstream{"42"};
  auto lexer = lexer::Lexer{input};

  check_token<token::Number*, double>(&lexer, token::Type::kNumber, 42.);
}

TEST(Lexer, NumberNoDecimal) {
  const auto input = new std::istringstream{"42."};
  auto lexer = lexer::Lexer{input};

  check_token<token::Number*, double>(&lexer, token::Type::kNumber, 42.);
}

TEST(Lexer, NumberWithDecimal) {
  const auto input = new std::istringstream{"42.1337"};
  auto lexer = lexer::Lexer{input};

  check_token<token::Number*, double>(&lexer, token::Type::kNumber, 42.1337);
}

TEST(Lexer, SimpleExpr) {
  const auto input = new std::istringstream{"def f(a) a + 1"};

  auto lexer = lexer::Lexer{input};

  EXPECT_EQ(lexer.GetNextToken()->type, token::Type::kDef);
  check_token<token::Identifier*, std::string>(&lexer, token::Type::kIdentifier, "f");
  EXPECT_EQ(lexer.GetNextToken()->type, token::Type::kLParen);
  check_token<token::Identifier*, std::string>(&lexer, token::Type::kIdentifier, "a");
  EXPECT_EQ(lexer.GetNextToken()->type, token::Type::kRParen);
}
