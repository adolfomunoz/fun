# fun 
A C++17 header-based library for functional programming.

This library provides a set of [Haskell-like](http://www.haskell.org) functional programming tools. Thanks to template metaprogramming, the evaluation of such functions is lazy, so it is possible to deal with infinite lists. Furthermore, polimorphic functions can be used as parameters. This requires the use of several features of C++17, which are supported only in modern compilers.

## Compiling the examples
There are several examples inside the folder [main](main). You can clone the repository and compile, for instance, the example 'simple-function' (git + gcc) as follows:
```
git clone https://github.com/adolfomunoz/fun.git

g++ --std=c++17 -O3 fun/main/doc/simple-function/simple-function.cc -o simple-function
```

There is also a `CMakeLists.txt` if you'd rather use [cmake](https://cmake.org/).

The `-O3` option is recommended for ensuring comparable performance with respect to non-functional approaches to solving the same problems. There is no further dependency apart from a C++17 capable compiler. It has been tested (not extensively) with:
* gcc 7.x (and its MinGW64 counterpart).

## Usage

TO-DO

## Documentation
This library is still a work in progress (we are in the process of redesign), and its documentation is therefore a work in progress over a work in progress (meaning it is incomplete). You can find some simple examples that help documentation in the [main/doc](main/doc) folder.

The [doc](doc) folder is outdated but will be reviewed later.

## Comparison with other functional libraries

This section is not entirelly updated.

There are other open source libraries that focus on functional programming:
* [FTL](https://github.com/beark/ftl) - Awesome library that accounts fur sum types, pattern matching and monad-like structures (none of those are done by our library). As this `fun` library, it is also able to curry functions.
* [fpcpp](https://github.com/jdduke/fpcpp) - Another awesome library. It is actually very similar to `fun`, and it is more developed. It is pre-C++14 so it has required a huge amount of extra work.
* [Boost Phoenix](http://www.boost.org/doc/libs/1_58_0/libs/phoenix/doc/html/) - A very stable functional programming library. It enables lazy function and value evaluation, and pre-C++11 lambda functions. It is rather extensive. I frankly did not find its syntax very appealing, but it seems very interesting to explore and research because it included functional programming in a pre-C++11 compiler.

Note that I have not tried any of these libraries extensively, so I might be wrong about something. Please let me know if this is the case, or if I have missed any important library.

## Disclaimer
This code is released under the [GNU Public License V3 licence](http://www.gnu.org/licenses/gpl-3.0-standalone.html). In practice, if you use this code I'd like the following to happen:
* Let me know that you are using it.
* Let me know how can it be improved.
