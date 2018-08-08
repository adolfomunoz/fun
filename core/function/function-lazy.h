#pragma once

#include "function.h"

namespace fun {
//This helps the classes below to calculate the lazy value only once even if it 
//is called many times in the case of being copy assignable.
//By default does not copy anything
template<typename Ret,
	bool KeepAttribute = std::is_default_constructible_v<Ret> && (std::is_copy_assignable_v<Ret> || std::is_move_assignable_v<Ret>),
	bool KeepPointer = std::is_copy_constructible_v<Ret> || std::is_move_constructible_v<Ret>>
struct Evaluator {
public:
	template<typename F>
	Ret lazy(const F& f) const { return f(); }
};

//It can be constructed (without parameters) and copied or moved. Keep as copy
template<typename Ret,bool D>
struct Evaluator<Ret,true,D> {
	mutable bool first = true; 
	mutable Ret ret;
public:
	template<typename F>
	Ret lazy(const F& f) const 
	{ if (first) { ret = f(); first = false; } return ret; }
};

//Keep as pointer
template<typename Ret>
struct Evaluator<Ret,false,true> { 
	mutable Ret* ret = nullptr;
public:
	~Evaluator() { if (ret) delete ret; }
	template<typename F>
	Ret lazy(const F& f) const 
	{ if (!ret) ret = new Ret(f()); return *ret; }
};

//Special case for 0 parameter functions (can be evaluated and converted to ret (lazy evaluation))
template<typename F, typename Classes, typename Ret>
class Function_<F,Classes, Ret> : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;
	Evaluator<Ret> evaluator;
	operator Ret() const { return evaluator.lazy(this->f); }
};

//Special case for 0 parameter functions (can be evaluated and converted to ret (lazy evaluation)). If we reach this point and it is still generic, we deduce the type from the function call
template<typename F, typename Classes, std::size_t I>
class Function_<F,Classes, Generic<I>> : public FunctionBase<F> {
public:
	//NEED STATIC ASSERT HERE FOR CHECKING CLASS
	using FunctionBase<F>::FunctionBase;
	using Ret = decltype(std::declval<F>()());

	static_assert(class_check<Classes,I,Ret>::value, "Generic type is not an instance of class.");
	Evaluator<Ret> evaluator;
	operator Ret() const { return evaluator.lazy(this->f); }
};

//When outputting a lazy-evaluable function, we actually evaluate it
template<typename F, typename Classes, typename Ret>
std::ostream& operator<<(std::ostream& os, const Function_<F,Classes,Ret>& f) {
	os<<f.impl()(); return os;
}
	
}