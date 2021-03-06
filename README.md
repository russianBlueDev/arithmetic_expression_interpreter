arithmetic_expression_interpreter
=================================

Simple arithmetic expression evaluator written in C.


The language
============

The language will consist of integers and floating-point numbers with arithmetic operators
+, -, *, /, ^ (with priorities). It will support parenthezised expressions, variable and
function definition.

Maybe it will also have boolean operators OR, AND, EQUALS, NOT together with comparison
operators <, <=, >, >= in order to implement if conditions.

Goal
====

```
$>> 3 * -2.5
ans = -7.5

$>> x := (ans + 7) * 2
x = -1

$>> def abs(x) := if(x < 0) -x else x
abs(x) = if(x < 0) -x else x

$>> abs(ans)
ans = 7.5

$>> abs(x)
ans = 1
```

Building it
===========

You must have
* clang
* valgrind

and you just type

```
make
````

For code coverage report, you need also
* gcc (on MAC OS make sure it's not LLVM hidden behind gcc)
* gcov
* lcov (can be installed on MAC OS by compiling source and remove -D option from lcov/bin/install.sh)

and you enter

```
make coverage
```

