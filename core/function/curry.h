#ifndef _FUNCTIONAL_CURRY_H_
#define _FUNCTIONAL_CURRY_H_

#include <utility>

namespace fun {

template<typename F, typename Arg>
class Curry
{
	F   f;
	Arg a;
public:
	Curry(F&& _f,      Arg&& _a) : f(std::forward<F>(_f)), a(std::forward<Arg>(_a)) { }
	Curry(const F& _f, Arg&& _a) : f(_f), a(std::forward<Arg>(_a))                  { }
	Curry(F&& _f,      const Arg& _a) : f(std::forward<F>(_f)), a(_a) { }
	Curry(const F& _f, const Arg& _a) : f(_f), a(_a)                  { }

	template<typename... Args>
	auto operator()(Args&&... args) const 
	{	return f(a,std::forward<Args>(args)...);		}
};

/**************************************
 * fun::API  
 * Do not use, it is better to use the "function.h" API instead *
 **************************************/

template<typename F, typename Arg>
auto curry(F&& f, Arg&& a)
{	return Curry<typename std::remove_reference<F>::type,typename std::remove_reference<Arg>::type>(
		std::forward<F>(f),std::forward<Arg>(a));	
} 

template<typename F, typename Arg, typename... Args>
auto curry(F&& f, Arg&& a, Args&&... args)
{	return curry(Curry<typename std::remove_reference<F>::type,typename std::remove_reference<Arg>::type>(
			std::forward<F>(f), std::forward<Arg>(a)), 
	       std::forward<Args>(args)...);
}

}; //namespace fun

#endif
