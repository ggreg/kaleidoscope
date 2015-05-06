# Who is the author?

I am Greg Leclercq, a software engineer who is fascinated by hardware
architectures, operating systems, compilers, programming languages, and
distributed systems.

I work as a backend and infrastructure engineer.

Note: I would love to see people contribute to this project. Please add
yourself to this page as a contributor when it happens :).

# Why LLVM?

LLVM is becoming ubiquituous in compilers. It is the backend of the
[clang](http://clang.org) C++ compiler and recent languages such as
[Rust](http://www.rust-lang.org), [Julia](http://julialang.org) and
[Swift](https://developer.apple.com/swift/) use it. What makes LLVM so
interesting is the infrastructure it provides to generate code. You can benefit
from Just-in-Time (JIT) compilation, a debugguer, interoperability between
languages for example.

# Why this tutorial?

I started to follow the original LLVM Tutorial in C++ and found it very
practical. While writing the code I asked myself questions and made thought
experiments. I needed to understand the language even if it is very simple. I
also like to plan things and make a mental representation before implementing
them. Then I experiment. I adapted the tutorial to make my own version and make
what I learn stick. My first intention was selfish but I believe it may benefit
to other people to have what I can share.

It was for me a way to learn more about LLVM and to
write a project in C++. As I was versed into modern C++ I could prevent myself
from trying to use features from the C++11 and C++14 standards. I also prefered
putting code in several modules. Then I was missing tests and a build system. I
finally decided to write this project to conciliate the learning of LLVM,
writing a compiler, and practicing C++.
