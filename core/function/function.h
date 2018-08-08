#pragma once

#include <utility>
#include <tuple>
#include <iostream>
#include "../type/type.h"
#include "../type/classes.h"

//This replaces something that will happen in C++20
namespace std {
template< class T >
struct remove_cvref {
    typedef remove_cv_t<remove_reference_t<T>> type;
};	

template< class T >
using remove_cvref_t = typename remove_cvref<T>::type;
}

//Watch out: const char* parameters are problematic with currying
namespace fun {
	
//Handles construction of functions
template<typename F>
class FunctionBase
{
protected:
	F   f;
public:
	constexpr FunctionBase(F&& f)      : f(std::forward<F>(f)) { }
	constexpr FunctionBase(const F& f) : f(f) { }

	//Implementation details, do not use
	const F& impl() const { return f; }
};

//Handles construction of functions, specialization for function pointers (standard C++ functions)
template<typename F>
class FunctionBase<F&>
{
protected:
	F&   f;
public:
	constexpr FunctionBase(const F& f) : f(f) { }
	const F& impl() const { return f; }
};


template<typename F, typename Classes, typename... Args>
class Function_ : public FunctionBase<F> { };

namespace detail {
	template<typename F> //Callable object considered by default
	struct function_deduction { 
		static constexpr auto generate(F&& f) {
			return function_deduction<decltype(&F::operator())>::generate(std::forward<F>(f));
		}
		static constexpr auto generate(const F& f) {
			return function_deduction<decltype(&F::operator())>::generate(f);
		}
	};

	template<typename Ret, typename... Args>
	struct function_deduction<Ret (Args...)> {
		template<typename F>
		static constexpr auto generate(const F& f) { 
			return Function_<const std::remove_cvref_t<F>&,classes_default_t,std::remove_cvref_t<Ret>,std::remove_cvref_t<Args>...>(f); 
		}
	};

	template<typename Class, typename Ret, typename... Args>
	struct function_deduction<Ret (Class::*)(Args...) const> {
		template<typename F>
		static constexpr auto generate(F&& f) { 
			return Function_<std::remove_cvref_t<F>,classes_default_t, std::remove_cvref_t<Ret>,std::remove_cvref_t<Args>...>(std::forward<F>(f)); 
		}
	};
	
	template<typename T, std::size_t... I>
	auto tuple_elements(const T& t, std::index_sequence<I...>) {
		return std::tuple(std::get<I>(t)...);
	}
	
	template<typename... Args>
	auto tuple_reorder(const std::tuple<Args...>& t) {
		return std::tuple_cat(std::tuple(std::get<sizeof...(Args)-1>(t)),
			tuple_elements(t, std::make_index_sequence<sizeof...(Args)-1>{}));
	}

	template<typename F, typename Classes, typename T>
	struct function_from_tuple { };
	
	template<typename F, typename Classes, typename... Args>
	struct function_from_tuple<F,Classes,std::tuple<Args...>> {
		using type = Function_<F,Classes,Args...>;
	};
	
	template<typename F, typename Classes, typename... Args>
	struct function_reorder {
		using type = typename function_from_tuple<F,Classes,
			decltype(tuple_reorder(std::declval<std::tuple<Args...>>()))>::type;
	};
	
	template<typename F, typename Classes, typename Ret>
	struct function_reorder<F,Classes, Ret> {
		using type = Function_<F,Classes, Ret>;
	};

	template<std::size_t I, typename NewType, typename Arg, typename... Args>
	struct tuple_replace_generic {
		using type = decltype(std::tuple_cat(std::declval<std::tuple<Arg>>(),
				std::declval<typename tuple_replace_generic<I,NewType,Args...>::type>()));
	};
	
	template<std::size_t I, typename NewType, typename Arg>
	struct tuple_replace_generic<I, NewType, Arg> {
		using type = std::tuple<Arg>;
	};
	
	template<std::size_t I, typename NewType, typename... Args>
	struct tuple_replace_generic<I,NewType,Generic<I>,Args...> {
		using type = decltype(std::tuple_cat(std::declval<std::tuple<NewType>>(),
				std::declval<typename tuple_replace_generic<I,NewType,Args...>::type>()));		
	};	

	template<std::size_t I, typename NewType>
	struct tuple_replace_generic<I, NewType, Generic<I>> {
		using type = std::tuple<NewType>;
	};
		
	template<typename F, typename Classes, std::size_t I, typename NewType, typename Arg, typename... Args>
	struct function_replace_generic {
		using type = typename function_from_tuple<F, Classes, decltype(tuple_reorder(std::declval<typename tuple_replace_generic<I,NewType,Arg,Args...>::type>()))>::type;
	};

	template<typename F, typename Classes, std::size_t I, typename NewType, typename Arg>
	struct function_replace_generic<F,Classes, I,NewType,Arg> {
		using type = typename function_from_tuple<F, Classes, typename tuple_replace_generic<I,NewType,Arg>::type>::type;
	};

		
	template<typename... Args> 
	struct function_aux { 
		template<typename F>
		static constexpr auto generate(F&& f) {
			return (typename function_reorder<std::remove_cvref_t<F>,classes_default_t,Args...>::type)(std::forward<F>(f)); 
		}
		template<typename F>
		static constexpr auto generate(const F& f) {
			return (typename function_reorder<std::remove_cvref_t<F>,classes_default_t,Args...>::type)(f); 
		}
		template<typename R, typename... A>
		static constexpr auto generate(R f(A...)) {
			return (typename function_reorder<decltype(f),classes_default_t,Args...>::type)(f); 			
		}
	};
	
	template<typename... Classes, typename... Args>
	struct function_aux<std::tuple<Classes...>,Args...> {
		template<typename F>
		static constexpr auto generate(F&& f) {
			return (typename function_reorder<std::remove_cvref_t<F>,std::tuple<Classes...>,Args...>::type)(std::forward<F>(f)); 
		}
		template<typename F>
		static constexpr auto generate(const F& f) {
			return (typename function_reorder<std::remove_cvref_t<F>,std::tuple<Classes...>,Args...>::type)(f); 
		}
		template<typename R, typename... A>
		static constexpr auto generate(R f(A...)) {
			return (typename function_reorder<decltype(f),std::tuple<Classes...>,Args...>::type)(f); 			
		}		
	};

	template<typename Classes, std::size_t I, typename NewType, typename... Args> 
	struct function_replace_aux { 
		template<typename F>
		static constexpr auto generate(F&& f) {
			return (typename function_replace_generic<std::remove_cvref_t<F>,Classes, I, NewType,Args...>::type)(std::forward<F>(f)); 
		}
		template<typename F>
		static constexpr auto generate(const F& f) {
			return (typename function_replace_generic<std::remove_cvref_t<F>,Classes, I, NewType,Args...>::type)(f); 
		}
		template<typename R, typename... A>
		static constexpr auto generate(R f(A...)) {
			return (typename function_replace_generic<decltype(f),Classes, I, NewType,Args...>::type)(f); 			
		}
	};

	template<typename T>
	struct function_from_type_aux{};

	//Final implementation in type.h
	
};

template<typename Classes, std::size_t I, typename NewType, typename A1, typename... Args, typename F>
auto function_replace(F&& f) {
	return detail::function_replace_aux<Classes, I, NewType, A1, Args...>::generate(std::forward<F>(f));
}


template<typename T, typename F>
auto function_from_type(F&& f) {
	return detail::function_from_type_aux<T>::generate(std::forward<F>(f));
}

template<typename A1, typename... Args, typename F>
auto function(F&& f) {
	return detail::function_aux<A1, Args...>::generate(std::forward<F>(f));
}

template<typename F>
auto function(F&& f) {
	return detail::function_deduction<std::remove_cvref_t<F>>::generate(std::forward<F>(f));
}

//This helps the classes below to calculate the lazy value only once even if it 
//is called many times in the case of being copy assignable.
//By default does not copy anything
template<typename Ret,
	bool KeepAtrribute = std::is_default_constructible_v<Ret> && (std::is_copy_assignable_v<Ret> || std::is_move_assignable_v<Ret>),
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

template<typename F, typename Arg>
class Curried {
	F f;
	Arg arg;
public:
	Curried(F&& f, Arg&& arg) : f(std::forward<F>(f)), arg(std::forward<Arg>(arg)) { }
	Curried(const F& f, Arg&& arg) : f(f), arg(std::forward<Arg>(arg))             { }
	Curried(F&& f, const Arg& arg) : f(std::forward<F>(f)), arg(arg)               { }
	Curried(const F& f, const Arg& arg) : f(f), arg(arg)                           { }

	template<typename... Args>
	auto operator()(Args&&... args) const {
		return f(arg, std::forward<Args>(args)...);
	}

/*
	template<typename... Args>
	auto operator()(const Args&... args) const {
		return f(arg, args...);
	}*/
};


template<typename F, typename Arg>
class Curried<F&,Arg> {
	F& f;
	Arg arg;
public:
	Curried(const F& f, Arg&& arg) : f(f), arg(std::forward<Arg>(arg))             { }
	Curried(const F& f, const Arg& arg) : f(f), arg(arg)                           { }

	template<typename... Args>
	auto operator()(Args&&... args) const {
		return f(arg, std::forward<Args>(args)...);
	}
};
//General case for 1 or more parameters
template<typename F, typename Classes, typename Ret, typename Arg, typename... Args>
class Function_<F,Classes, Ret,Arg,Args...> : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;
	
	auto operator()(Arg&& arg) const { //Currying
		return function<Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Arg>>(this->f,std::forward<Arg>(arg)));
	}

	auto operator()(const Arg& arg) const { //Currying
		return function<Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Arg>>(this->f,arg));
	}
	
	template<typename FArg, typename FClasses>
	auto operator()(Function_<FArg,FClasses,Arg>&& arg) const {//Currying with lazy evaluation
		return function<Classes,Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Function_<FArg,FClasses,Arg>>>(this->f,std::forward<Function_<FArg,FClasses,Arg>>(arg)));	
	}
	
	template<typename FArg, typename FClasses>
	auto operator()(const Function_<FArg,FClasses,Arg>& arg) const {//Currying with lazy evaluation
		return function<Classes,Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Function_<FArg,FClasses,Arg>>>(this->f,arg));	
	}

	//A1 instead of Arg in order to enable lazy evaluation of parameters.
	template<typename A1, typename A2, typename... Args2>
	auto operator()(A1&& arg, A2&& a2, Args2&&... args2) const { // Full call
		return ((*this)(std::forward<A1>(arg)))
			(std::forward<A2>(a2),std::forward<Args2>(args2)...);
	}
};

//General case for 1 or more parameters with a generic argument
template<typename F, typename Classes, typename Ret, std::size_t I, typename... Args>
class Function_<F,Classes,Ret,Generic<I>,Args...> : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;
	
	template<typename Arg> //It is indeed generic
	auto operator()(Arg&& arg) const { //Currying
		static_assert(class_check<Classes,I,Arg>::value, "Generic type is not an instance of class.");
		//We will need to static assesrt the class of Arg
		//We need to replace Generic<I> with Arg in Args... and Ret
		return function_replace<Classes,I,Arg,Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Arg>>(this->f,std::forward<Arg>(arg)));
	}

	template<typename Arg> //It is indeed generic	
	auto operator()(const Arg& arg) const { //Currying
		static_assert(class_check<Classes,I,Arg>::value, "Generic type is not an instance of class.");
		//We would need to replace Generic<I> with Arg in Args... and Ret
		return function_replace<Classes,I,Arg,Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Arg>>(this->f,arg));
	}
	
	template<typename FArg, typename FClasses, typename Arg> // It is indeed generic
	auto operator()(Function_<FArg,FClasses,Arg>&& arg) const {//Currying with lazy evaluation
		static_assert(class_check<Classes,I,Arg>::value, "Generic type is not an instance of class.");
		//We would need to replace Generic<I> with Arg in Args... and Ret
		return function_replace<Classes,I,Arg,Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Function_<FArg,FClasses,Arg>>>(this->f,std::forward<Function_<FArg,FClasses,Arg>>(arg)));	
	}
	
	template<typename FArg, typename FClasses, typename Arg> // It is indeed generic
	auto operator()(const Function_<FArg,FClasses,Arg>& arg) const {//Currying with lazy evaluation
		static_assert(class_check<Classes,I,Arg>::value, "Generic type is not an instance of class.");
		//We would need to replace Generic<I> with Arg in Args... and Ret
		return function_replace<Classes,I,Arg, Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Function_<FArg,FClasses,Arg>>>(this->f,arg));	
	}
	
	//A1 instead of Arg in order to enable lazy evaluation of parameters, although
	// it does not matter here in the generic version
	template<typename A1, typename A2, typename... Args2>
	auto operator()(A1&& arg, A2&& a2, Args2&&... args2) const { // Full call
		return ((*this)(std::forward<A1>(arg)))
			(std::forward<A2>(a2),std::forward<Args2>(args2)...);
	}
};


}; //namespace fun

