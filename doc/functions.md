# About functions 

## Sections

As in Haskell, the partial application of an infix operator is called a section. The syntax is slightly different than Haskell, though:

```
using fun::_;
//Creating section with + infix operator
auto add_one = _+1;
//Using the resulting function
std::cout<<add_one(3)<<std::endl;
//Outputs 4
```

Note that the parenthesis are no longer required (in Haskell, they are). Instead, the sectioned parameter must be identified by `fun::_`. This syntax is therefore more appealing with the line `using fun::_` and from that line the symbol `_` represents sectioning.

For a two parameter sectioning, just use the `_` symbol twice:

```
using fun::_;
//Creating the two-parameter section with the == infix operator
auto are_equal = _==_;
//Using the resulting function
if (are_equal(3,3))  std::cout<<"3 and 3 are equal"<<std::endl;
if (!are_equal(3,4)) std::cout<<"3 and 4 are not equal"<<std::endl;
```

All C++ infix operators (numerical, relational, logical and bitwise) can be sectioned using this approach.

## Composition

All functions defined in `fun` can be composed, with the `*` operator. The `.` operator (used in Haskell) cannot be redefined in C++.

```
using fun::_;
auto is_multiple_of_three = (_==0) * (_%3);
//Equivalent:
//auto is_multiple_of_three = [] (int n) { return (n%3)==0; }
if (is_multiple_of_three(33)) std::cout<<"33 is multiple of 3"<<std::endl; 
else std::cout<<"33 is not multiple of 3"<<std::endl;
if (is_multiple_of_three(71)) std::cout<<"71 is multiple of 3"<<std::endl; 
else std::cout<<"71 is not multiple of 3"<<std::endl;
```

Note that function composition only works for functions defined within the `fun` library. For C++11 lambda functions, or any other function, you should turn them into `fun` functions as explained below.

## Currying and partial application

Currying is the process of transforming a function that takes multiple arguments into a function that takes just a single argument and returns another function if any arguments are still needed. As in Haskell, all functions in `fun` are curried, in the sense that they can be considered as having a single argument and returning a function (or value, if the original function had a single parameter). This allows partial application of parameters. 

The first example is with the `pow` function (which is the `fun` version of the standard C++ `pow` function).

```
std::cout<<fun::pow(2,4)<<std::endl;
//Outputs 16

//We omit the second parameter
auto power_of_two = fun::pow(2);

std::cout<<power_of_two(3)<<std::endl;
//Outputs 8
std::cout<<power_of_two(8)<<std::endl;
//Outputs 256

``` 

In Haskell, currying is a basic mechanism of the language, and as such there are functions that only make sense with such feature. For instance, Haskell's `const` function takes two parameters and always returns the first one. Such definition seems unneeded, but with partial application, it is actually a generator of constant functions.

As `const` is a C++ reserved keyworkd, in `fun` such function is named `constant`, as in the following example:

```
auto one = fun::constant(1);

std::cout<<one(32)<<std::endl;
//Outputs 1
std::cout<<one("what")<<std::endl;
//Outputs 1	
``` 

Note that default currying only works for functions defined within the `fun` library. For C++11 lambda functions, or any other function, you should turn them into `fun` functions as explained below.


## Flip

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


## Including C++ functions

While in many circumstances new functions can be easily defined from the constructions discussed above, it might happen that a new function is required and it is not obvious (or even impossible) how to do that. This would be the case, for instance, of user defined classes. 

In those cases, the `fun` library provides the `function` function, which has a template parameter that defines the number of parameters of the function being created.

```
//<1> is the number of parameters
auto fun_atoi = fun::function<1>([] (const char* s) { return atoi(s); }); 
std::cout<<(fun_atoi("3")+fun_atoi("2"))<<std::endl;
//Outputs 5
```

The newly created function, apart from being used normally (as if defined in C++) includes all the functional features that `fun` functions have, such as currying and function composition.

```
//<3> is the number of parameters
auto clamp = fun::function<3>(
	[] (float low, float high, float value) {
		return ((value<low)?low:((value>high)?high:value));
});
std::cout<<clamp(-10.0f,10.0f,9.0f)<<std::endl;
//Outputs 9 
std::cout<<clamp(-10.0f,10.0f,11.0f)<<std::endl;
//Outputs 10

//We apply currying and function composition to create gamma curve from clamped values
auto gamma = fun::flip(fun::pow)(1.0f/2.2f) * clamp(0.0f, 1.0f);
std::cout<<gamma(0.9f)<<std::endl;
//Outputs 0.953238
std::cout<<gamma(1.2f)<<std::endl;
//Outputs 1
```

Note that this enables, in practice, to include new functions with side effects (pointer editing, for instance). That is definitelly not advised. It seems quite weird to use a library for functional programming and then include a side effect that destroys the foundation of functional programming. 

## Currying - returning functions

As stated before, all functions in `fun` are curried, in the sense that multiple argument functions can be considered as single argument functions returning a new function. This enables partial application. 

Furthermore, when defining new functions it is also possible to return another function. Instead of cumbersome notations with multiple opening and closing parameters, `fun` can interpret functions that return functions as functions with extra parameters. This is, coceptually, the opposite of partial application.

```
//Checks if an integer is multiple of another one.
auto is_multiple_of	= fun::function<2>([] (int a, int b) { return (a%b)==0; });
if (is_multiple_of(14,7)) std::cout<<"14 is multiple of 7"<<std::endl;	

//The same, but taking advantage of currying
auto is_multiple_of_c	= fun::function<1>([] (int a) { return (_==0) * (a%_); });
if (is_multiple_of_c(14,7)) std::cout<<"14 is multiple of 7"<<std::endl;
// instead of is_multiple_of(14)(7)	
```

In Haskell, this is not needed because functions can be directly defined by means of equations with partial application. As this is not syntactically possible in C++, the closest thing to it is this option, as illustrated in the example above.



