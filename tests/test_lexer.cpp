#include <iostream>
#include <string>

#include "gtest/gtest.h"

#include "lexer.hpp"

using namespace kaleidoscope;


TEST(Lexer, Identifier) {
  const auto input = new std::istringstream{"var"};
  auto lexer = lexer::Lexer(input);

  auto next_tok = boost::get<token::TokenWithValue>(lexer.GetNextToken());

  EXPECT_EQ(next_tok->type, token::Type::kIdentifier);
  EXPECT_EQ(next_tok->value, token::Value("var"));
}

TEST(Lexer, NumberInt) {
  const auto input = new std::istringstream{"42"};
  auto lexer = lexer::Lexer{input};

  auto next_tok = boost::get<token::TokenWithValue>(lexer.GetNextToken());

  EXPECT_EQ(next_tok->type, token::Type::kNumber);
  EXPECT_EQ(next_tok->value, token::Value(42.));
}

TEST(Lexer, NumberNoDecimal) {
  const auto input = new std::istringstream{"42."};
  auto lexer = lexer::Lexer{input};

  auto next_tok = boost::get<token::TokenWithValue>(lexer.GetNextToken());

  EXPECT_EQ(next_tok->type, token::Type::kNumber);
  EXPECT_EQ(next_tok->value, token::Value(42.));
}

TEST(Lexer, NumberWithDecimal) {
  const auto input = new std::istringstream{"42.1337"};
  auto lexer = lexer::Lexer{input};

  auto next_tok = boost::get<token::TokenWithValue>(lexer.GetNextToken());

  EXPECT_EQ(next_tok->type, token::Type::kNumber);
  EXPECT_EQ(next_tok->value, token::Value(42.1337));
}
