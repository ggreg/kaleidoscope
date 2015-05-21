#include <cstdio>
#include <cstdlib>
#include <string>
#include <memory>

#include "lexer.hpp"


namespace kaleidoscope {

namespace lexer {

void Lexer::SkipSpaces() {
  while(isspace(GetChar())) {
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

  return nullptr;
}

} // End of namespace: lexer

} // End of namespace: kaleidoscope
