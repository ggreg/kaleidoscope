#include <cstdio>
#include <cstdlib>
#include <string>
#include <memory>

#include "lexer.hpp"


namespace kaleidoscope {

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
      while (isalnum((last_char_ = input_->get()))) {
        value += last_char_;
      }

      if (value == "def") {
        return new token::Token{token::Type::kDef};
      }

      return new token::Token{
        token::TokenWithValue{token::Type::kIdentifier, value}
      };
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

    return new token::Token{
      token::TokenWithValue{token::Type::kNumber, strtod(number_str.c_str(), 0)}
    };
  }

  return nullptr;
}

} // End of namespace: lexer

} // End of namespace: kaleidoscope
