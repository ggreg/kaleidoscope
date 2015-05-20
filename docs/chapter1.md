# A small subset of the language

## Function Definition

In this chapter we will focus on a small part of the language. Our goal is to
be able to define and call functions.

A function is defined by its:

- Signature that contains the name of the function and its arguments.
- Body that describes the computation that will be applied to its arguments
  when  the function will be called.

Once a function is defined, one can call it by using its name and replacing the
name of arguments by values.

For example, we define a `add` function there:

```python
def add(a, b)
    a + b
```

And we call it with:

```python
add(1, 2)
```

Why do we need the `def` keyword? It is a way to make it easier to distinguish
the definition and the calling of a function. It helps the parsing steps and
avoid to look ahead to make decision of what the expression is. Let's do a
thought experiment and imagine we don't use the `def` keyword. Now we define
the function with:

```python
add(a, b)
    a + b
```

The first token is `add`, we call it an *identifier*. The next one is `(`. This
is exactly the same as the calling of a function `add(1, 2)`. If we compare
both we have:

- Definition: `identifier ( identifier , identifier)`
- Call: `identifier ( number , number)`

So we need to look ahead two tokens to know if we parse a definition or a call.
It would be even worse if the language supported variables! The parser would
encounter situations such as the *call* is also `identifier ( identifier ,
identifier )`. It would then be forced to get tokens after the `)`. Using the
`def` keyword removes any ambiguity from the start of the definition.

One more thing, the indentation is only here for readability. It is not part of the body format. We could write:

```python
add(a, b) a + b
```

## Frontend

Ok, so now how can we parse that?

The frontend relies on two components: the lexer and the parser. The lexer
reads the raw text of the source code and converts it to a sequence of tokens.
A token identifies the type of an expression, it has a type and a value. For
example we said earlier that `add` is an identifier. So its type is
`identifier` and its value is `add`. The parser reads the sequence of tokens
and matches grammar rules. A grammar descripe the structure of the language. In
other word it explains the set of valid token sequences.

### Lexer

The first step is to implement the lexer. We don't need to keep the value for
all tokens. 

At this stage, we want to support the following token:

- end-of-file EOF
- `def`
- `identifier` with a string value (for example `add`).
- `number` with a `double` value (for example `1.234`).

The original LLVM tutorial used two global variables:

- One to store the value of an *identifier* as a `string`: `static std::string IdentifierStr; // Filled in if tok_identifier`.
- Another to store the value of a *number* as a `double`: `static double NumVal; // Filled in if tok_number`.

What's wrong with that?

We cannot parse two tokens at the same time (in different threads or coroutines) but should it really happen? Parallel compilation usually relies on separate processes.

There is a performance issue related to global variable that would not be often
in the cache. They are declared *static* so they are stored in the `.bss
uninitialized` section while most of the time the stack is hot. However at this
stage, performance is not a concern.

In our context, the main concern is *locality* and its consequence on
understanding how and when a variable is used. Hence a global variable makes it
harder to reason about what piece of code is using it and when. It also makes
it more difficult to write tests. See also [GlobalVariablesAreBad](http://c2.com/cgi/wiki?GlobalVariablesAreBad) and [Are global variables bad?](http://stackoverflow.com/a/485020).

Another simple way to handle that is to define a struct:

```c++
enum struct TokenType {  // enum struct is C++11.
  eof        = -1,
  def        = -2,
  identifier = -3,
  number     = -4, // Trailing comma authorized in C++11.
};
```

Note: an *enum struct* (or an *enum class*) is a *scoped enumeration*. It
allows to address its value with their enum prefix (here `TokenType::`) also
called *scope resolution operator. See also
[enum](http://en.cppreference.com/w/cpp/language/enum). There is no collision between
two scoped enumerations. For example we can have a `Enum1::A` and `Enum2::A`.
There are no implicit conversions from the values of a scoped enumerator to
integral types, although static_cast may be used to obtain the numeric value of
the enumerator. It means you can convert `TokenType` to an integer with `static_cast<int>(type)`, for example:

```c++
cout << static_cast<int>TokenType::identifier << endl;
```

will print:

```
-3
```

```cpp
struct Token {
  TokenType type;
  TokenValue value;
};
```

There are several issues there:

- *type* and *value* can mismatch, for example having a identifier with an
  integer value. It would be a bug in the lexer though.
- `TokenValue` has several subtypes like `double` and `string`.

To solve the problem of mismatch between *type* and *value*, we can rely on a type hierarchy:

```cpp
struct Token {
  TokenType type;
  TokenValue value;
};

struct Identifier: public Token {
  static const TokenType type = TokenType::identifier;
  string value;

  Identifier(string value): value{value} {}
};

struct Number: public Token {
  static const TokenType type = TokenType::number;
  double value;

  Number(double value): value{value} {}
};
```

To solve the problem of `TokenValue` that have several types, we use
[Boost.Variant](http://www.boost.org/libs/variant). These also [*The Boost
C++ libraries, Chapter
24. Boost.Variant*](http://theboostcpplibraries.com/boost.variant):

```c++
#include <boost/variant.hpp>

//...

typedef boost::variant<char, string, double> TokenValue;
```

Then, the following code:

```c++
  auto tok = Identifier("def");
  cout << tok.value << endl;
  cout << static_cast<int>(tok.type) << endl;
```

prints:

```
def
-3
```

Note: there is something wrong with `Token tok = Identifier("def")` where
`tok.value` is empty (I assume it is initialized by default to the empty string
by the compiler). [Object
Slicing](https://en.wikipedia.org/wiki/Object_slicing)??

What will happen when we will need to inspect the type of `Token` instance?
There is a problem. The class and its `type` attribute are redundant. The class
hierarchy does not represent the fact that some tokens are identified
*dynamically*. This is why the token types are negative. It's to automatically
take into account characters integer value. It means the scanning step cannot
go through basic sanity checks. The lexer allows invalid tokens. To make it stricter we can define all the valid tokens.o

```c++
class Token {
  int type;
  Value value;
}
```

Then we will have a factory that takes a string and returns a `Token`:

```c++
Token* mkToken(std::string str) {

}
```

How does it compare to a simple integer? With a naive approach we will allocate
one new object for each token even simple one such as `(` or `)`. A bit
advantae of an integer is that it is a native value, it does not require any
allocation.

Why not using Boost.Variant again? And define:

```c++
typedef boost::variant<int, TokenWithValue> Token;
```

It brings the best of both world:

- Native value for tokens that can be represent only with their ordinal value
- Type and value in a class for tokens that has a value. Some have a static
  alue (`"def"`) other have a dynamic value (for example a function `f` is an
  identifier with value `f`).

A visitor will help to define a strategy to get the value.

The original LLVM tutorial uses a function to get the next token from the
input. It assumes that the input comes from *stdin* hence using the `getchar()`
function from `cstdio` and that values are stored in global variables when
needed. This design would be hard to evolve when we will want to support some
error handling. Don't you like the error reporting expressiveness and accuracy
of clang? ;)

```c++
#include <iostream>


class Lexer {
    int line_number_;
    int char_offset_;
    char current_char_;
    Token last_token_;
    std::istream input_;

  public:
    Lexer(std::istream input) input_{input} {}
    Token& GetNextToken();
}
```

Here the private attributes encapsulate the state and we can evolve the class
without disturbing its users. We can define what we expect in tests. The lexer
is very simple that's why there is no issue implementing it in functions rather
than defining regular expressions. However regular would be more expressive.
Let's start with a simple version and see if we want to refactor it.
