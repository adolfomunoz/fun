#ifndef _FUNCTIONAL_CAST_H_
#define _FUNCTIONAL_CAST_H_

#include <memory>
#include "forward-list.h"

namespace fun
{

template<typename T>
constexpr std::true_type  is_forward_list(const ForwardListPolymorphic<T>&) { return std::true_type(); }
constexpr std::false_type is_forward_list(...) { return std::false_type(); }

template<typename T, typename forward = decltype(is_forward_list(std::declval<T>())), typename bidirectional = std::false_type, typename random_access = std::false_type>
struct cast {
	using type = T;
	static const bool is_forward_list       = false;
	static const bool is_bidirectional_list = false;
	static const bool is_random_access_list = false;
};

template<typename T>
struct cast<T, std::true_type, std::false_type, std::false_type> {
	using type = ForwardList<typename T::value_type>;
	static const bool is_forward_list       = true;
	static const bool is_bidirectional_list = false;
	static const bool is_random_access_list = false;
};

};


#endif
