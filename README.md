# fun 
A C++14 header-based library for functional programming.

This library provides a set of [Haskell-like](http://www.haskell.org) functional programming tools. Thanks to template metaprogramming, the evaluation of such functions is lazy, so it is possible to deal with infinite lists. Furthermore, polimorphic functions can be used as parameters. This requires the use of several features of C++14, which are supported only in modern compilers.

As it is shown in the examples, the performance is very close to basic C++ implementations of the same functions.

## What this library does not do
As oposed to Haskell, this library does not do:
* Pattern matching
* Type checking (apart from the standard C++ huge template errors)
* Lazy evaluation of everything (just of the lists that are returned by our implemented functions)

## Compiling the examples
There are several examples:
* [fun-dot](https://github.com/adolfomunoz/fun/blob/master/examples/fun-dot.cc) computes the dot product of two vectors represented by very large `std::list<double>`. It compares the performance of three different implementations of such dot product, including a basic C++ loop, C++ function based on the 'fun' library and a pure `fun`-generated function.
* [fun-norm](https://github.com/adolfomunoz/fun/blob/master/examples/fun-norm.cc) computes the *i-esm* norm.
* [fun-primes](https://github.com/adolfomunoz/fun/blob/master/examples/fun-primes.cc) creates an infinite list of prime numbers and prints part of it using different strategies (`take` and `takeWhile`).

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
which is an infinite list of prime numbers, or
```
auto dot = fun::compose(fun::sum, fun::curry(fun::zipWith, std::multiplies<double>()));
```
which is a function that calculates the dot product of two vectors (represented as lists or generally speaking anything iterable).

## Comparison with other functional libraries

There are other open source libraries that focus on functional programming:
* [FTL](https://github.com/beark/ftl) - Awesome library that accounts fur sum types, pattern matching and monad-like structures (none of those are done by our library). As this `fun` library, it is also able to curry functions.
* [fpcpp](https://github.com/jdduke/fpcpp) - Another awesome library. It is actually very similar to `fun`, and it is more developed. It is pre-C++14 so it has required a huge amount of extra work.
* [Boost Phoenix](http://www.boost.org/doc/libs/1_58_0/libs/phoenix/doc/html/) - A very stable functional programming library. It enables lazy function and value evaluation, and pre-C++11 lambda functions. It is rather extensive. I frankly did not find its syntax very appealing, but it seems very interesting to explore and research because it included functional programming in a pre-C++11 compiler.

Note that I have not tried any of these libraries extensively, so I might be wrong about something. Please let me know if this is the case, or if I have missed any important library.

## Disclaimer
This code is released under the [GNU Public License V3 licence](http://www.gnu.org/licenses/gpl-3.0-standalone.html). In practice, if you use this code I'd like the following to happen:
* Let me know that you are using it.
* Let me know how can it be improved.
