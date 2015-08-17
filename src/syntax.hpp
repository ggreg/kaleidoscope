#include <vector>


namespace kaleidoscope {

namespace ast {

class Expr {
public:
  virtual ~Expr() {}
};

class Number: public Expr {
public:
  Number(double value):
    value_{value} {}
  double Value() { return value_; }

private:
  double value_;
};

class Variable: public Expr {
public:
  Variable(const std::string& name):
    name_{name} {}
  std::string Name() { return name_; }

private:
  std::string name_;
};

using Args = std::vector<std::string>*;

class FunctionPrototype: public Expr {
public:
  FunctionPrototype(const std::string name, std::vector<std::string>* arguments):
    name_{name},
    arguments_{arguments} {}
  std::string Name() { return name_; }
  Args Arguments() { return arguments_; }

private:
  std::string name_;
  std::vector<std::string>* arguments_;
};

class FunctionDefinition: public Expr {
public:
  FunctionDefinition(FunctionPrototype* prototype, Expr* body):
    prototype_{prototype},
    body_{body} {}
  FunctionPrototype* Prototype() { return prototype_; }
  Expr* Body() { return body_; }

private:
  FunctionPrototype* prototype_;
  Expr* body_;
};

class FunctionCall: public Expr {
public:
  FunctionCall(std::string name, std::vector<std::string>* arguments):
    name_{name},
    arguments_(arguments) {}
  std::string Name() { return name_; }
  Args Arguments() { return arguments_; }

private:
  std::string name_;
  std::vector<std::string>* arguments_;
};

} // End of namespace: ast

namespace syntax {

class Parser {
public:
  Parser(std::istream* input):
    input_{input},
    lexer_{new lexer::Lexer{input}} {};
  ast::Expr* Parse();
  ast::FunctionDefinition* ParseFunctionDefinition();
  ast::FunctionCall* ParseFunctionCall();
  ast::FunctionPrototype* ParseFunctionPrototype();
  std::vector<std::string>* ParseFunctionArguments();
  void ParseLParen();
  void ParseRParen();

private:
  std::istream* input_;
  lexer::Lexer* lexer_;
};

} // End of namespace: syntax

} // End of namespace: kaleidoscope
