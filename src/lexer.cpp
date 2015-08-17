#include <cstdio>
#include <cstdlib>
#include <string>
#include <memory>

#include "lexer.hpp"


namespace kaleidoscope {

namespace token {
  const Type Identifier::type = Type::kIdentifier;
  const Type Number::type = Type::kNumber;
}

namespace lexer {

void Lexer::SkipSpaces() {
  while(isspace(last_char_)) {
    GetChar();
  }
}


char Lexer::GetChar() {
  last_char_ = input_->get();
  return last_char_;
}


token::Token* Lexer::GetNextToken() {
  SkipSpaces();

  auto token = last_char_;
  if (isalpha(last_char_)) {
      std::string value;
      value += last_char_;
      while (isalnum(GetChar())) {
        value += last_char_;
      }

      if (value == "def") {
        token_ = new token::Token{token::Type::kDef};
        return token_;
      }

      token_ = new token::Identifier{value};
      return token_;
  }
  if (isdigit(last_char_)) {
    std::string number_str;
    number_str += last_char_;

    while (isdigit(GetChar())) {
      number_str += last_char_;
    }
    if (last_char_ == '.') {
      number_str += last_char_;

      while (isdigit(GetChar())) {
        number_str += last_char_;
      }
    }

    token_ = new token::Number{strtod(number_str.c_str(), 0)};
    return token_;
  }
  if (last_char_ == '(') {
    GetChar();

    token_ = new token::Token(token::Type::kLParen);
    return token_;
  }
  if (last_char_ == ')') {
    GetChar();
    token_ = new token::Token(token::Type::kRParen);
    return token_;
  }

  return nullptr;
}

} // End of namespace: lexer

} // End of namespace: kaleidoscope
