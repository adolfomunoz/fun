#pragma once

#include "generic.h"
#include "generic-replacement.h"
#include <type_traits>

namespace fun {

template<typename TypeID, typename... Params>
struct type {};
 
template<typename T, typename U>
struct match {
	static constexpr bool value = std::is_same<T,U>::value; 
};

}
