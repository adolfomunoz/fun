# Function generators

Find here all functions that have functions as parameters, and return new functions.

## constant

In Haskell, currying is a basic mechanism of the language, and as such there are functions that only make sense with such feature. For instance, Haskell's `const` function takes two parameters and always returns the first one. Such definition seems unneeded, but with partial application, it is actually a generator of constant functions.

As `const` is a C++ reserved keyworkd, in `fun` such function is named `constant`, as in the following example:

```
auto one = fun::constant(1);

std::cout<<one(32)<<std::endl;
//Outputs 1
std::cout<<one("what")<<std::endl;
//Outputs 1	
``` 

Currying is described [here](functions.md).

## flip

In `fun` (as in Haskell) the function `flip` takes a two-parameter function and returns a new function with both parameters with switched order.

```
std::cout<<fun::pow(2,5)<<std::endl;
//Outputs 32

auto flipped_pow = fun::flip(fun::pow);
std::cout<<flipped_pow(2,5)<<std::endl;
//Outputs 25, as if the parameters of fun::pow were exchanged
```

It becomes useful when combined with other functional features such as currying.

```
//Currying, we omit the second parameter of the flipped function
auto cube = fun::flip(fun::pow)(3);

std::cout<<cube(5)<<std::endl;
//Outputs 125
std::cout<<cube(3)<<std::endl;
//Outputs 27
``` 

Currying is described [here](functions.md).

## uncurry
Currying is the process of transforming a function that takes multiple arguments into a function that takes just a single argument and returns another function if any arguments are still needed. As in Haskell, all functions in `fun` are curried, in the sense that they can be considered as having a single argument and returning a function (or value, if the original function had a single parameter). Currying is described [here](functions.md).

The function `uncurry` (and its specific `fun` variations) does the oposite: transforms a curried function into a function that takes a single parameter (a tuple, in Haskell) that aglutinates all its parameters.

```
auto ut_pow = fun::uncurry(fun::pow);
//Now ut_pow expects a tuple with the two parameters for fun::pow
std::cout<<ut_pow(std::make_tuple(2,4))<<std::endl;
//Outputs 16
```

This is similar to Haskell's `uncurry` function. However, in `fun` we provide two more `uncurry` variations that present some shortcommings but provide useful and efficient alternatives.

One of these alternatives is `uncurry_list`, which, instead of a tuple, expects a list with all the parameters.

```
auto ul_pow = fun::uncurry_list(fun::pow);
//Now ul_pow expects a list with the two parameters for fun::pow
std::cout<<ul_pow(fun::l(2,4))<<std::endl;
//Outputs 16
```
This `uncurry` variation has two limitations: first, all the elements of any list are of the same type. Therefore the applicability of `uncurry_list` is limited to functions that have all the parameters of the same type (or automatically convertible from the same type). Furthermore, there cannot be a static compilation check on the number of elements on the list, so it might unexpectedly explode if the number of elements of the list is smaller than the number of parameters of the function.

The other alternative has the advantage of efficiency (besides its multiple risky limitations): sometimes you need to traverse the elements of a list, applying them to different functions, and doing it in a functional way is inefficient (`take` and `drop` combinations). Furthermore, the programmer might not know in advance the number of parameters of each of the functions, or these may be different. For that purpose, `uncurry_iterator` uncurries a function with an iterator over a list of parameters and advances such iterator.

```
auto ui_pow = fun::uncurry_iterator(fun::pow);
//Now ul_pow expects an iterator over a list
auto params = fun::l(2,4,3,3);
auto iter   = params.begin();
//Warning: side effect (iter is modified)
std::cout<<ui_pow(iter)<<std::endl;
//Outputs 16
//Warning: iter has advanced as required (two steps). Again, side effect (iter is modified)
std::cout<<ui_pow(iter)<<std::endl;
//Outputs 27
```
Besides the limitations of `uncurry_list` (same type of parameters and no static size compilation check), `uncurry_iterator` advances the input iterator, so it has side effects (which are wrong for pure functional programming). Also, depending on the position of the iterator, it might reach the end of the list within a function call, which would explode in run time.

The higher order function `explore` (which is not included in Haskell, but only in `fun`) takes advantage of `uncurry_iterator` by traversing a list through the iterator and returning the function while in the list.
```
auto ui_pow = fun::uncurry_iterator(fun::pow);
auto params = fun::l(2,4,3,3);
std::cout<<fun::explore(ui_pow, params)<<std::endl;
//Outputs [16, 27], a list with two elements.
```



