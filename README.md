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

Compilation
===========

You must have
* gcc (on MAC OS make sure it's not LLVM hidden behind gcc cmd). For now, in the Makefile, it's gcc-4.2
* gcov
* lcov (can be installed on MAC OS by compiling source and remove -D option from lcov/bin/install.sh)
* valgrind

