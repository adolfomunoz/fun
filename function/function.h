#ifndef _FUNCTIONAL_FUNCTION_H_
#define _FUNCTIONAL_FUNCTION_H_

#include "compose.h"
#include "curry.h"
#include <utility>

namespace fun {

template<typename F>
class FunctionBase
{
protected:
	F   f;
public:
	FunctionBase(F&& _f)      : f(std::forward<F>(_f)) { }
	FunctionBase(const F& _f) : f(_f) { }
	
	template<typename... Args>
	auto operator()(Args&&... args) const 
	{	return f(std::forward<Args>(args)...);		}

	/**
	 * Used for public visibility on implementation details. Never use in reality.
	 **/
	const F& f_() const { return f; }
};

template<unsigned int N, typename F>
class Function : public FunctionBase<F>
{
public:
	using FunctionBase<F>::FunctionBase;
};

template<unsigned int N, typename F>
auto function(F&& f) { return Function<N,F>(f); }

template<unsigned int N, typename F>
auto function(const F& f) { return Function<N,F>(f); }

template<typename F>
class Function<1,F> : public FunctionBase<F>
{
public:
	using FunctionBase<F>::FunctionBase;

	template<typename A1>
	auto operator()(A1&& a1) const
	{	return (this->f)(std::forward<A1>(a1));   }

	/**
	 * Composition operator
	 **/
	template<unsigned int NThat, typename FThat>
	auto operator&(Function<NThat, FThat>&& that) const 
	{	return function<NThat>(compose(this->f, std::forward<const FThat>(that.f_())));    }
	template<unsigned int NThat, typename FThat>
	auto operator&(const Function<NThat, FThat>& that) const 
	{	return function<NThat>(compose(this->f, that.f_()));    }

};

template<typename F>
class Function<2,F> : public FunctionBase<F>
{
public:
	using FunctionBase<F>::FunctionBase;

	template<typename A1, typename A2>
	auto operator()(const A1& a1, const A2& a2) const
	{	return (this->f)(a1, a2);   }

	/**
	 * Currying operator
	 **/
	template<typename A1>
	auto operator()(A1&& a1) const
	{	return function<1>(curry(this->f,std::forward<A1>(a1)));   }
};

template<typename F>
class Function<3,F> : public FunctionBase<F>
{
public:
	using FunctionBase<F>::FunctionBase;

	template<typename A1, typename A2, typename A3>
	auto operator()(const A1& a1, const A2& a2, A3&& a3) const
	{	return (this->f)(a1, a2,a3);   }

	/**
	 * Currying operator
	 **/
	template<typename A1, typename A2>
	auto operator()(A1&& a1, A2&& a2) const
	{	return function<1>(curry(this->f,std::forward<A1>(a1), std::forward<A2>(a2)));   }

	/**
	 * Currying operator
	 **/
	template<typename A1>
	auto operator()(A1&& a1) const
	{	return function<2>(curry(this->f,std::forward<A1>(a1)));   }
};

}; //namespace fun

#endif
