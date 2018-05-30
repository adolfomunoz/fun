#ifndef _FUNCTIONAL_FLIP_H_
#define _FUNCTIONAL_FLIP_H_

#include "function.h"

namespace fun {


template<typename F>
class Flip
{
	F   f;
public:
	Flip(F&& _f)      : f(std::forward<F>(_f)) { }
	Flip(const F& _f) : f(_f)                  { }

	template<typename Arg1, typename Arg2>
	auto operator()(Arg1&& arg1, Arg2&& arg2) const 
	{	return f(std::forward<Arg2>(arg2),std::forward<Arg1>(arg1));	}
};

template<typename F>
auto flip_(F&& f) 
{	return function<2>(Flip<typename std::remove_reference<F>::type>(std::forward<F>(f)));   } 

/**************************************
 * fun::API                           *
 **************************************/

auto flip = function<1>([] (auto&& f) { return flip_(f); });

}; //namespace fun

#endif
