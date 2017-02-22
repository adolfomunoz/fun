# Higher order list functions

## map 
Applies a unary function to every single element of a list:

```
fun::map(<function>,<list>)
```

Example:

```
using fun::_;
auto l = fun::range(1,5);
//l is [1,2,3,4,5]
auto ml = fun::map(1+_,l);
//ml is [2,3,4,5,6]
```

Internally, the evaluation is lazy, and therefore it can deal with infinite lists:

```
using fun::_;
auto l = fun::range(1);
//l is [1,2,3,4,5,...]
auto ml = fun::map(2*_,l);
//ml is [2,4,6,8,10,...]
```

It has all the features that `fun` functions have. It therefore can be curried:

```
using fun::_;
auto square_list = fun::map([] (int i) { return i*i; });
//square_list is a function that squares all elements on a list
auto ml = square_list(fun::range(1,5));
//ml is [1,4,9,16,25]
```

Find [here](http://hackage.haskell.org/package/base-4.8.2.0/docs/Prelude.html#v:map) its Haskell documentation.


## filter
Selects the subset of a list that fulfills a specific predicate:

```
fun::filter(<predicate>,<list>);
```

Example:

```
using fun::_;
auto l = fun::range(1,5);
//l is [1,2,3,4,5]
auto fl = fun::filter([] (int i) { return (i%2)==0; }, l);
//fl is [2,4]
```

Internally, the evaluation is lazy, and therefore it can deal with infinite lists:

```
using fun::_;
auto l = fun::range(1);
//l is [1,2,3,4,5,...]
auto fl = fun::filter(_>3,l);
//fl is [4,5,6,7,8,...]
```

It has all the features that `fun` functions have. It therefore can be curried:

```
using fun::_;
auto multiples_of_seven = fun::filter([] (int i) { return (i%7)==0; });
//multiples_of_seven is a function that gets the multiples of seven of a list
auto fl = multiples_of_seven(fun::range(0,20));
//fl is [0,7,14]
```

Find [here](http://hackage.haskell.org/package/base-4.8.2.0/docs/Prelude.html#v:filter) its Haskell documentation.

## zipWith
Applies a binary function to each element of a pair of lists, returning a new list. If the lists have different lengths, it sticks to the shorter:

```
fun::zipWith(<zipWith>,<list1>,<list2>);
```

Example:

```
using fun::_;
auto l1 = fun::range(1,5);
//l1 is [1,2,3,4,5]
auto l2 = fun::range(10,14,2);
//l2 is [10,12,14]
auto zl = fun::zipWith(_+_,l1,l2);
//zl is [11,14,17]
```

Internally, the evaluation is lazy, and therefore it can deal with infinite lists:

```
using fun::_;
auto l1 = fun::range(1);
//l1 is [1,2,3,4,5,...]
auto l2 = fun::range(2);
//l2 is [2,3,4,5,6,...]
auto zl = fun::zipWith(_*_,l1,l2);
//zl is [2,6,12,20,30,...]
```

It has all the features that `fun` functions have. It therefore can be curried:

```
using fun::_;
auto are_equal = fun::zipWith(_==_);
//are_equal is a function that given two lists returns true for every pair of equal elements
auto zl = are_equal(fun::range(1,3),fun::range(0,4,2));
//zl is [false,true,false]
```

Find [here](http://hackage.haskell.org/package/base-4.8.2.0/docs/Prelude.html#v:zipWith) its Haskell documentation.



