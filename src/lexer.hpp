#include <boost/variant.hpp>


namespace kaleidoscope {

namespace token {

enum struct Type {
  kEof,
  kDef,
  kIdentifier,
  kNumber,
  kLParen,
  kRParen, // Trailing comma authorized in C++11.
};

typedef boost::variant<std::string, double> Value;
struct TokenWithValue {
  Type type;
  Value value;
};

typedef boost::variant<Type, TokenWithValue> Token;
}

namespace lexer {

class Lexer {
  std::istream* input_;
  int last_char_;

  public:
    Lexer(std::istream* input):
      input_{input},
      last_char_{static_cast<int>(' ')} {
    }
    void SkipSpaces();
    char GetChar();
    token::Token* GetNextToken();
};

}

}
