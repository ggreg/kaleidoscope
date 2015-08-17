#include <iostream>
#include <string>
#include <typeinfo>

#include "gtest/gtest.h"

#include "lexer.hpp"
#include "syntax.hpp"

using namespace kaleidoscope;

TEST(Syntax, FunctionWithSingleArgument) {
  const auto input = new std::istringstream{"def f(a) g(a)"};
  auto parser = syntax::Parser(input);

  auto expr = static_cast<ast::FunctionDefinition*>(parser.Parse());
  auto funcName = typeid(*expr).name();
  EXPECT_TRUE(
      std::string(funcName).find("FunctionDefinition") != std::string::npos
  );
  EXPECT_EQ(expr->Prototype()->Name(), "f");
  auto defargs = *expr->Prototype()->Arguments();
  EXPECT_EQ(defargs[0], std::string("a"));
  auto body = static_cast<ast::FunctionCall*>(expr->Body());
  EXPECT_EQ(body->Name(), "g");
  auto callargs = *body->Arguments();
  EXPECT_EQ(callargs[0], "a");
}
