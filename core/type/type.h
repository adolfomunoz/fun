#pragma once

#include "generic.h"
#include <type_traits>

namespace fun {

template<typename TypeID, typename... Params>
struct type {};
 
template<typename T, typename U>
struct match {
	static constexpr bool value = std::is_same<TypeID,U>::value; 
};

template<typename TypeID, typename U>
struct match<type<TypeID>,U> {
	static constexpr bool value = std::is_same<TypeID,U>::value; 
};









}
