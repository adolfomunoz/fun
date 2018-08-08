#pragma once

#include "function.h"
#include "function-construction.h"

namespace fun {
namespace detail {
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
};

template<typename Classes, std::size_t I, typename NewType, typename A1, typename... Args, typename F>
auto function_replace(F&& f) {
	return detail::function_replace_aux<Classes, I, NewType, A1, Args...>::generate(std::forward<F>(f));
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
	
}