# Welcome to Kaleidoscope++

## Introduction

Welcome to this variant of the “Implementing a language with LLVM” tutorial.
This tutorial runs through the implementation of a simple language, showing how
fun and easy it can be. It will get you up and started as well as help to build
a framework you can extend to other languages. The code in this tutorial can
also be used as a playground to hack on other LLVM specific things.

The goal of this tutorial is to progressively unveil our language, describing
how it is built up over time. This will let us cover a fairly broad range of
language design and LLVM-specific usage issues, showing and explaining the code
for it all along the way, without overwhelming you with tons of details up
front.

This tutorial is an alternative to the official LLVM tutorial and tries to
follow modern and sane software engineering principles that are deliberately
missing from the original tutorial.

## Requirements

You should have a basic understanding of C or C++, mainly static types and
manual memory allocation. As the code will rely on some modern (C++11, C++14)
features, we will use the Boost library, pointer ownership and move semantics.
Though they are not the main topic of the tutorial, it is a good use case for
these kind of features.

## The Kaleidoscope Language

This tutorial will be illustrated with a toy language that we’ll call
“Kaleidoscope” (derived from “meaning beautiful, form, and view”). Kaleidoscope
is a procedural language that allows you to define functions, use conditionals,
math, etc. Over the course of the tutorial, we’ll extend Kaleidoscope to
support the if/then/else construct, a for loop, user defined operators, JIT
compilation with a simple command line interface, etc...

To keep things simple, we start with a single data type: a 64-bit floating type
(aka *double* in C parlance). Hence we do not have to declare the type of a
variable and it gives the language a taste of dynamically typed language. We
will see how to make it evolve and support multiple types later.

Kaleidoscope supports the definition of functions such as:

```python
def fib(x)
  if x < 3 then
    1
  else
    fib(x - 1) + fib(x - 2)
```

This function is callable as:

```python
fib(40)
```
