#pragma once

namespace fun {
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
	

	template<typename F, typename Classes, typename... Args>
	struct function_reorder {
		using type = typename function_from_tuple<F,Classes,
			decltype(tuple_reorder(std::declval<std::tuple<Args...>>()))>::type;
	};
	
	template<typename F, typename Classes, typename Ret>
	struct function_reorder<F,Classes, Ret> {
		using type = Function_<F,Classes, Ret>;
	};
		
	template<typename... Args> 
	struct function_aux { 
		template<typename F>
		static constexpr auto generate(F&& f) {
			return (typename function_reorder<std::decay_t<F>,classes_default_t,Args...>::type)(std::forward<F>(f)); 
		}
		template<typename F>
		static constexpr auto generate(const F& f) {
			return (typename function_reorder<std::decay_t<F>,classes_default_t,Args...>::type)(f); 
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
			return (typename function_reorder<std::decay_t<F>,std::tuple<Classes...>,Args...>::type)(std::forward<F>(f)); 
		}
		template<typename F>
		static constexpr auto generate(const F& f) {
			return (typename function_reorder<std::decay_t<F>,std::tuple<Classes...>,Args...>::type)(f); 
		}
		template<typename R, typename... A>
		static constexpr auto generate(R f(A...)) {
			return (typename function_reorder<decltype(f),std::tuple<Classes...>,Args...>::type)(f); 			
		}		
	};
};


template<typename A1, typename... Args, typename F>
auto function(F&& f) {
	return detail::function_aux<A1, Args...>::generate(std::forward<F>(f));
}

template<typename F>
auto function(F&& f) {
	return detail::function_deduction<std::remove_cvref_t<F>>::generate(std::forward<F>(f));
}
	
};