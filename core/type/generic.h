#pragma once

namespace fun {
	
template<std::size_t I>
struct Generic {}; 
//Represents a generic type

namespace generic {
	using a = Generic<1>;
	using b = Generic<2>;
	using c = Generic<3>;
	using d = Generic<4>;
	using e = Generic<5>;
	using f = Generic<6>;
	using g = Generic<7>;
	using h = Generic<8>;
}	
	
};