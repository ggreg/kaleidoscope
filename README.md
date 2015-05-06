# README for Kaleidoscope++

## Introduction

This is an extended version of the LLVM tutorial: a compiler for the
Kaleidoscope language. It brings some engineering practices that are
deliberately missing from the original tutorial. The purpose of this version is
to provide the foundation to write compilers for toy languages. It tries to
introduce concepts more progressively at the beginning by focusing on a smaller
scope and building on examples. Then it moves beyond the original tutorial.

The following engineering practices are part of Kaleidoscope++:

- Uses Git to show how the code evolves.
- Google C++ Coding Style and inspiration from LLVM Coding standard: it's
  present in other open source projects, even outside Google's ones, and it
  carries lessons learned from experienced.
- Documents the source code with doxygen.
- Comes with a command to analyze syntax: clean that uses `clang-check`.
- Builds with gyp + ninja: because it helps to iterate faster when
  modifying the code.
- Unit tests (using Google Test): to explain the small parts.
- Integration tests: to explain the big picture.
- Logging (using Boost.Log): to show what's happening and they are useful
  to understand and debug.
- Modularity: code is architectured across modules.

As an project, it's not perfect and any suggestions and modifications to
improve it are warmly welcome. Fork it, hack it, share it!

## Requirements

- C++ compiler (clang or g++)
- gyp
- ninja
- googletest
- mkdocs

## Quick Start

The project provides the following commands (use `./help` to discover them):

- check: the source code with static analysis.
- ctags: build ctags.
- bootstrap: use gyp to generate ninja files.
- build: the kc (stands for *kaleidoscope compiler*) executable.
- test: launch the test suite.
- clean: remove object and executable files.

## Tutorial

Please find the tutorial in the `docs/` directory in the form of one
markdown file per chapter. It uses the [mkdocs](http://www.mkdocs.org/) tool
to generate a static site of the documentation.

Refer to the [mkdocs](http://www.mkdocs.org/) site for further details.

To install it:

```
$ pip install mkdocs
```

To start the built-in webserver and browse the tutorial, type:

```
$ mkdocs serve
```

Then open up http://127.0.0.1:8000/ in your browser.

If you want to generate the static site, type:

```
$ mkdocs build
```

It will create a new directory, named `site/` and put HTML and static files
inside.

## Acknowledgements

I'd like to thanks the many authors and contributors to the open source
projects used here. They made this project possible and helped to learn
so many things.

Special thanks to the authors of the original [LLVM
Tutorial](http://llvm.org/docs/tutorial/index.html) and all people involved in
the LLVM project.
