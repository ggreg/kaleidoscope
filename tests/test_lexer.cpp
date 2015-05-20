#include <iostream>
#include <string>

#include "gtest/gtest.h"

#include "lexer.hpp"

using namespace kaleidoscope;


TEST(Lexer, Identifier) {
  const std::string val = "var";
  const auto input = new std::istringstream{val};
  auto tok = token::TokenWithValue{
    token::Type::kIdentifier,
     "var",
  };

  auto lexer = lexer::Lexer(input);
  auto next_tok = boost::get<token::TokenWithValue>(lexer.GetNextToken());
  EXPECT_EQ(next_tok->type, tok.type);
  EXPECT_EQ(next_tok->value, tok.value);
}
