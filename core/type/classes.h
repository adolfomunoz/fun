#pragma once

namespace fun {
	
	
struct None {
	template<typename T>
	struct check {
		static constexpr bool value = true;
	};
};	

template<typename C1, typename C2>
struct And {
	template<typename T, 
		 typename check1 = typename C1::template check<T>,
		 typename check2 = typename C2::template check<T> >
	struct check {
		static constexpr bool value = check1::value && check2::value;
	};
};
	
struct classes_default {
	using type = std::tuple<None>;
};

using classes_default_t = classes_default::type;

namespace detail {
    template <std::size_t I, typename Tuple, bool IsInTuple = (I < std::tuple_size_v<Tuple>)>
    struct classes_expand_element {
	using type = None;
    };

    template <std::size_t I, typename Tuple>
    struct classes_expand_element<I,Tuple,true> {
	using type = typename std::tuple_element<I, Tuple>::type;
    };
	
    template<typename Tuple, typename Indices>
    struct classes_expand_sequence { };

    template<typename Tuple, std::size_t... I>
    struct classes_expand_sequence<Tuple, std::integer_sequence<std::size_t, I...>> {
	using type = std::tuple<typename classes_expand_element<I,Tuple>::type... >;
    };


    template<typename Tuple, std::size_t N>
    struct classes_expand {
	using type = typename classes_expand_sequence<Tuple, std::make_index_sequence<std::max(N,std::tuple_size_v<Tuple>)>>::type;
    };

    template<typename Tuple, std::size_t Index, typename NewClass, typename Indices>
    struct classes_combine_sequence { };

    template<typename Tuple, std::size_t Index, typename NewClass, std::size_t... I>
    struct classes_combine_sequence<Tuple, Index, NewClass, std::integer_sequence<std::size_t, I...>> {
  	using type = std::tuple<typename std::conditional<I==Index, And<NewClass,typename std::tuple_element<I,Tuple>::type>, typename std::tuple_element<I,Tuple>::type>::type...>;
    };

    template<typename Tuple, std::size_t Index, typename NewClass>
    struct classes_combine {
	using type = typename classes_combine_sequence<Tuple, Index, NewClass, std::make_index_sequence<std::tuple_size_v<Tuple>>>::type;
    };	
}

template<typename T1, typename T2, typename... T>
struct classlist { };

template<typename Class, std::size_t I, typename... More>
struct classlist<Class,Generic<I>,More...> {
	using type = typename detail::classes_combine<typename detail::classes_expand<classlist<More...>,I+1>::type, I, Class>::type;  
};

template<typename Class, std::size_t I>
struct classlist<Class,Generic<I>> {
	using type = typename detail::classes_combine<typename detail::classes_expand<classes_default_t,I+1>::type, I, Class>::type;  
};


template<typename T1, typename T2, typename... T>
using classes = typename classlist<T1,T2,T...>::type;

template<typename Classes, std::size_t I, typename T> 
using class_check = typename detail::classes_expand_element<I, Classes>::type::template check<T>;
}
