# Mixing fun and STL 

## STL

The STL provides its own collection structures, that can be generated as follows:

```
std::list<int> create(unsigned int size) {
	std::list<int> sol;
	for (unsigned int i = 0;i<size;++i) {
		sol.push_back((i%5) - 2);
	}
	return sol;
}
````

Since C++11, thanks to *move constructors* (and generally speaking, [move semantics and rvalue references](http://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html) ) C++ detects the existance of temporary objects (such as the return value of the above function) and *move* them (instead of copying them), such as in the following code:

```
	std::list<int> l = create(size); //Move constructor
	sol = 0;
    for (int i : l) if ((i % 2) == 0) sol+=5*i; 
```

The list `std::list<int> l` is **not copied, but moved** from the return value of `create(size)`, therefore constructing it in constant time. The above code will be used as the C++ performance reference.

## Copying in `fun`

In `fun` there are several features, such as [currying](functions.md) or the lazy evaluation of [higher order list functions](higher_order.md) use intermediate data structures which are transparent to the user. However, they require **copying** the input parameters. This is so because just const referencing the input parameters of such intermediate data structures would forbid the possibility of returning them from a function, where such reference could point to the activation stack of a no-longer-existing function.  

When using `fun` list generators such as `range` or when combining different higher order list functions (ej. `map` and then `filter`) the information to copy is not specially big, so the effect of copying on performance is negligible. However, copying a big STL structure could greatly damage runtime efficiency.u

In the following code (which is equivalent to the basic C++ code above), the list `l` is copied by `fun::filter` into the corresponding intermediate data structure (which is then moved by `fun::map`):

```
	std::list<int> l = create(size); //Move constructor
	sol = fun::sum(fun::map(_*5,fun::filter( (_==0)*(_%2),l))); 
```

The performance of such approach is our tests between 2 and 3 times slower than the C++ reference code above.

## Moving in `fun`

Then code shown as a counterexample which not only is rather slow but it actually does not look so functional as we are using the intermediate variable `std::list<int> l`. A more functional way of doing the same thing would be:

```
	sol = fun::sum(fun::map(_*5,fun::filter( (_==0)*(_%2),create(size))));
```

This not only looks more functional but triggers move semantics because the return value of `create(size)` is temporary. This leads to a performance equal to the C++ reference.

**Note :** In some compilers (MinGW 6.x) we have found out that this approach requires longer time, up to 150% the time of the reference. We are not sure why, but our design choices force move semantics in order to reach the performance of the reference solution. We are still trying to detect performance bottlenecks.

## Polymorphic lists

Another approach to the same solution is through `fun`'s polymorphic lists:

```
	fun::list<int> l = create(size); //Move constructor to polymorphic list
	sol = fun::sum(fun::map(_*5,fun::filter( (_==0)*(_%2),l)));
```

`fun::list<int> l` is a runtime-polymorphic time. It internally holds a smart pointer to a polymorphic data structured that can be copied and moved without any performance penalty. However, the use of dynamic method association through virtual method tables hinders performance. It is just slightly faster than copying the whole list, but it can be copied and move around at constant efficiency.

## List references

Our last proposed approach presents the same performance than the C++ reference solution (sometimes even faster, depending on the compiler). It uses `fun`'s list references:

```
	std::list<int> l = create(size);
	auto rl = fun::list_ref(l); 
	sol = fun::sum(fun::map(_*5,fun::filter( (_==0)*(_%2),rl)));
```

`rl` is a reference to `l` and as such there is no copy (nor move) or data, just a reference. While this solution is efficient, it uses reference internally, so there is a risk of memory access errors, in circumstances as the following:

```
auto f() {
	std::list<int> l = create(size);
	auto rl = fun::list_ref(l); 
	return fun::map(_*5,fun::filter( (_==0)*(_%2),rl));
}
```

Note that the returned intermediate data structure holds a reference to `std::list<int> l` which becomes unavailable once function `f()` has finished.

## Disclaimer

We are always working on improving the efficiency of our approach. In some cases (move semantics and list refrences) we reach the same performance than the C++ reference (with all optimization flags activated, of course). Note that this is not the case in some compilers (MingGW 6.x, for instance).

If you are using this library, please compile [the whole code](../examples/doc/fun-stl-copy-move.cc) and let us know if the performance rate of the four presented approaches (in your system, with your compiler).
