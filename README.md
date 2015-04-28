# fun 
A C++14 header-based library for functional programming.

This library provides a set of [Haskell-like](http://www.haskell.org) functional programming tools. Thanks to template metaprogramming, the evaluation of such functions is lazy, so it is possible to deal with infinite lists. Furthermore, polimorphic functions can be used as parameters. This requires the use of several features of C++14, which are supported only in modern compilers.

As it is shown in the examples, the performance is very close to basic C++ implementations of the same functions.

## What this library does not
As oposed to Haskell, this library does not check for types.

## Compiling the examples
There is an [example](https://github.com/adolfomunoz/qdt/blob/master/examples/fun-dot.cc) that computes the dot product of two vectors represented by very large `std::list<double>`. Different ways are compared.

You can clone the repository and compile the example (git + gcc) as follows:
```
git clone https://github.com/adolfomunoz/fun.git
g++ --std=c++14 fun/examples/fun-dot.cc  -o fun-dot
g++ --std=c++14 fun/examples/fun-norm.cc -o fun-norm
```

## Usage
```

## Disclaimer

This code is released under the [GNU Public License V3 licence](http://www.gnu.org/licenses/gpl-3.0-standalone.html). In practice, if you use this code I'd like the following to happen:
* Let me know that you are using it.
* Let me know how can it be improved.
