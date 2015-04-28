#ifndef _FUNCTIONAL_FLIP_H_
#define _FUNCTIONAL_FLIP_H_

#include <utility>

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

/**************************************
 * fun::API                           *
 **************************************/

template<typename F>
auto flip(F&& f)
{	return Flip<typename std::remove_reference<F>::type>(std::forward<F>(f));   } 

}; //namespace fun

#endif
