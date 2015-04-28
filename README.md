# fun 
A C++14 header-based library for functional programming.

This library provides a set of [Haskell-like](http://www.haskell.org) functional programming tools. Thanks to template metaprogramming, the evaluation of such functions is lazy, so it is possible to deal with infinite lists. Furthermore, polimorphic functions can be used as parameters. This requires the use of several features of C++14, which are supported only in modern compilers.

As it is shown in the examples, the performance is very close to basic C++ implementations of the same functions.

## What this library does not do
As oposed to Haskell, this library does not do:
* Pattern matching
* Type checking (apart from the standard C++ huge template errors)
* Lazy evaluation of everything (we

## Compiling the examples
There are several examples:
* [fun-dot](https://github.com/adolfomunoz/qdt/blob/master/examples/fun-dot.cc) computes the dot product of two vectors represented by very large `std::list<double>`. It compares the performance of three different implementations of such dot product, including a basic C++ loop, C++ function based on the 'fun' library and a pure `fun`-generated function.
* [fun-norm](https://github.com/adolfomunoz/qdt/blob/master/examples/fun-dot.cc) computes the *i-esm* norm

You can clone the repository and compile the example (git + gcc) as follows:
```
git clone https://github.com/adolfomunoz/fun.git
g++ --std=c++14 -O3 fun/examples/fun-dot.cc    -o fun-dot
g++ --std=c++14 -O3 fun/examples/fun-norm.cc   -o fun-norm
g++ --std=c++14 -O3 fun/examples/fun-primes.cc -o fun-primes
```

The `-O3` option is recommended for ensuring comparable performance with respect to non-functional approaches to solving the same problems. There is no further dependency apart from a C++14 capable compiler. It has been tested with:
* clang 3.5 
* gcc 4.9.2 (and its MinGW64 counterpart)

## Usage
The library is thought as a Haskell clone, focusing on higher order list functions such as `map`, `filter`, `repeat`, `iterate`... The code right now it is not documented except from the included examples (work in progress). 

It enables awesome one-liners such as
```
auto primes = fun::filter(
	[] (unsigned long n) { return !fun::any(
		fun::compose(fun::curry(std::equal_to<long>(),0), fun::curry(std::modulus<long>(),n)),
			fun::range(2,n-1)); },
	fun::range(1));
```
which is an infinite list of prime numbers. Lazy evaluation enables such stuff.

## Disclaimer
This code is released under the [GNU Public License V3 licence](http://www.gnu.org/licenses/gpl-3.0-standalone.html). In practice, if you use this code I'd like the following to happen:
* Let me know that you are using it.
* Let me know how can it be improved.
