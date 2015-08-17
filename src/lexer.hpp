#include <iostream>


namespace kaleidoscope {

namespace token {

enum struct Type {
  kEof,
  kDef,
  kIdentifier,
  kNumber,
  kLParen,
  kComma,
  kRParen, // Trailing comma authorized in C++11.
};

struct Token {
  Type type;

  Token(Type type): type{type} {};
};

struct Identifier: Token {
  static const Type type; // = Type::kIdentifier
  std::string value;

  Identifier(std::string value): Token{type}, value{value} {};
};

struct Number: Token {
  static const Type type; // = Type::kNumber;
  double value;

  Number(double value): Token{type}, value{value} {};
};

}

namespace lexer {

class Lexer {
public:
    Lexer(std::istream* input):
      input_{input},
      last_char_{static_cast<int>(' ')} {
    }
    void SkipSpaces();
    char GetChar();
    token::Token* GetNextToken();
    token::Token* CurrentToken() { return token_; };

private:
  std::istream* input_;
  int last_char_;
  token::Token* token_;
};

}

}
