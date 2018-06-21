#pragma once

namespace fun {

struct Eq {
	template<typename T>
	struct check {
		template<typename U>
	     	auto test(U*) -> typename std::is_same<decltype(std::declval<U>() == std::declval<U>()), bool>::type;
                template<typename>
                static constexpr std::false_type test(...);

		static constexpr bool value = decltype(test<T>(nullptr))::value; 
       	};
};

}
