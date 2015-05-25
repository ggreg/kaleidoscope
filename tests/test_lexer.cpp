#include <iostream>
#include <string>

#include "gtest/gtest.h"

#include "lexer.hpp"

using namespace kaleidoscope;


TEST(Lexer, Identifier) {
  const auto input = new std::istringstream{"var"};
  auto lexer = lexer::Lexer(input);

  auto next_tok = static_cast<token::Identifier*>(lexer.GetNextToken());

  EXPECT_EQ(next_tok->type, token::Type::kIdentifier);
  EXPECT_EQ(next_tok->value, "var");
}

TEST(Lexer, NumberInt) {
  const auto input = new std::istringstream{"42"};
  auto lexer = lexer::Lexer{input};

  auto next_tok = static_cast<token::Number*>(lexer.GetNextToken());

  EXPECT_EQ(next_tok->type, token::Type::kNumber);
  EXPECT_EQ(next_tok->value, 42.);
}

TEST(Lexer, NumberNoDecimal) {
  const auto input = new std::istringstream{"42."};
  auto lexer = lexer::Lexer{input};

  auto next_tok = static_cast<token::Number*>(lexer.GetNextToken());

  EXPECT_EQ(next_tok->type, token::Type::kNumber);
  EXPECT_EQ(next_tok->value, 42.);
}

TEST(Lexer, NumberWithDecimal) {
  const auto input = new std::istringstream{"42.1337"};
  auto lexer = lexer::Lexer{input};

  auto next_tok = static_cast<token::Number*>(lexer.GetNextToken());

  EXPECT_EQ(next_tok->type, token::Type::kNumber);
  EXPECT_EQ(next_tok->value, 42.1337);
}

TEST(Lexer, SimpleExpr) {
  const auto input = new std::istringstream{"def f(a) a + 1"};

  auto lexer = lexer::Lexer{input};

  auto tok1 = lexer.GetNextToken();
  EXPECT_EQ(tok1->type, token::Type::kDef);

  auto tok2 = static_cast<token::Identifier*>(lexer.GetNextToken());
  EXPECT_EQ(tok2->type, token::Type::kIdentifier);
  EXPECT_EQ(tok2->value, "f");

  auto tok3 = lexer.GetNextToken();
  assert(tok3 != nullptr);
  EXPECT_EQ(tok3->type, token::Type::kLParen);

  auto tok4 = static_cast<token::Identifier*>(lexer.GetNextToken());
  EXPECT_EQ(tok4->type, token::Type::kIdentifier);
  EXPECT_EQ(tok4->value, "a");

  auto tok5 = lexer.GetNextToken();
  assert(tok5 != nullptr);
  EXPECT_EQ(tok5->type, token::Type::kRParen);
}
