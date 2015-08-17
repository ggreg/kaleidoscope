#include <memory>
#include <string>
#include <cstdio>

#include "lexer.hpp"
#include "syntax.hpp"


namespace kaleidoscope {

namespace syntax {

ast::Expr* Parser::Parse() {
  auto curtok = lexer_->GetNextToken();

  switch (curtok->type) {
  case token::Type::kEof:
    return nullptr;
  case token::Type::kDef:
    return ParseFunctionDefinition();
  case token::Type::kIdentifier:
    return ParseFunctionCall();
  default:
    throw;
  }
}

ast::FunctionDefinition* Parser::ParseFunctionDefinition() {
  if (lexer_->CurrentToken()->type != token::Type::kDef) {
    // error
  }

  auto proto = ParseFunctionPrototype();
  auto body = Parse();

  return new ast::FunctionDefinition(proto, body);
}

ast::FunctionPrototype* Parser::ParseFunctionPrototype() {
  // current token is "def". Let's get the identifier i.e.
  // the function's name.
  auto function = static_cast<token::Identifier*>(lexer_->GetNextToken());
  if (function->type != token::Type::kIdentifier) {
    fprintf(stderr, "bad token %d", function->type);
    throw;
    // error
  }
  std::cout << function->value << std::endl;
  ParseLParen();
  auto arguments = ParseFunctionArguments();
  ParseRParen();

  return new ast::FunctionPrototype(function->value, arguments);
}

std::vector<std::string>* Parser::ParseFunctionArguments() {
  auto arguments = new std::vector<std::string>();

  while (lexer_->CurrentToken()->type != token::Type::kRParen) {
    auto tok = static_cast<token::Identifier*>(lexer_->GetNextToken());
    if (tok->type != token::Type::kIdentifier) {
      throw;
    }
    arguments->push_back(tok->value);
    lexer_->GetNextToken();  // ',' or ')'.
  }

  return arguments;
}

ast::FunctionCall* Parser::ParseFunctionCall() {
  auto function = static_cast<token::Identifier*>(lexer_->CurrentToken());
  ParseLParen();
  auto arguments = ParseFunctionArguments();
  ParseRParen();

  return new ast::FunctionCall(function->value, arguments);
}


void Parser::ParseLParen() {
  auto tok = lexer_->GetNextToken();
  if (tok->type != token::Type::kLParen) {
    throw;
  }
}

void Parser::ParseRParen() {
  auto tok = lexer_->CurrentToken();
  if (tok->type != token::Type::kRParen) {
    fprintf(stderr, "bad token %d", tok->type);
    throw;
  }
}

} // End of namespace: syntax

} // End of namespace: kaleidoscope
