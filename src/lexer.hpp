#include <boost/variant.hpp>


namespace kaleidoscope {

namespace token {

enum struct Type {
  kEof = -1,
  kDef = -2,
  kIdentifier = -3,
  kNumber = -4, // Trailing comma authorized in C++11.
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
    token::Token* GetNextToken();
};

}

}
