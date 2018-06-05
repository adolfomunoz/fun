#pragma once

namespace fun {
	
template<std::size_t I>
struct Generic {}; 
//Represents a generic type

namespace generic {
	using a = Generic<0>;
	using b = Generic<1>;
	using c = Generic<2>;
	using d = Generic<3>;
	using e = Generic<4>;
	using f = Generic<5>;
	using g = Generic<6>;
	using h = Generic<7>;
}	
	
};