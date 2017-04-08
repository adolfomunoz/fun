#ifndef _FUNCTIONAL_ZIPWITH_H_
#define _FUNCTIONAL_ZIPWITH_H_

#include "../../function/function.h"
#include "../core/forward-list.h"
#include <type_traits>
#include <tuple>
#include <functional>
#include <utility>
#include <memory>
#include <iostream>

namespace fun {

template<typename Function, typename List1, typename List2>
class ZippedWith : public ForwardListImpl<ZippedWith<Function,List1,List2>,decltype(std::declval<Function>()(std::declval<typename List1::value_type>(), std::declval<typename List2::value_type>()))>
{
	List1 list1;
	List2 list2; 
	Function function;
public:
	ZippedWith(Function&& function, List1&& list1, List2&& list2):
		list1(std::forward<List1>(list1)), list2(std::forward<List2>(list2)), function(std::forward<Function>(function)) { }
	ZippedWith(Function&& function, List1&& list1, const List2& list2):
		list1(std::forward<List1>(list1)), list2(list2), function(std::forward<Function>(function)) { }
	ZippedWith(Function&& function, const List1& list1, List2&& list2):
		list1(list1), list2(std::forward<List2>(list2)), function(std::forward<Function>(function)) { }
	ZippedWith(Function&& function, const List1& list1, const List2& list2):
		list1(list1), list2(list2), function(std::forward<Function>(function)) { }
	ZippedWith(const Function& function, List1&& list1, List2&& list2):
		list1(std::forward<List1>(list1)), list2(std::forward<List2>(list2)), function(function) { }
	ZippedWith(const Function& function, List1&& list1, const List2& list2):
		list1(std::forward<List1>(list1)), list2(list2), function(function) { }
	ZippedWith(const Function& function, const List1& list1, List2&& list2):
		list1(list1), list2(std::forward<List2>(list2)), function(function) { }
	ZippedWith(const Function& function, const List1& list1, const List2& list2):
		list1(list1), list2(list2), function(function) { }

	using value_type= typename ForwardListImpl<ZippedWith<Function,List1,List2>,decltype(std::declval<Function>()(std::declval<typename List1::value_type>(), std::declval<typename List2::value_type>()))>::value_type;

	class const_iterator_local 
	{
		friend class ZippedWith<Function, List1, List2>;
		typename List1::const_iterator i1; 
		typename List2::const_iterator i2;
		const ZippedWith<Function, List1, List2>* zw;

		const_iterator_local(const typename List1::const_iterator& _i1, 
			       const typename List2::const_iterator& _i2, 
			const ZippedWith<Function, List1, List2>* _zw) : i1(_i1), i2(_i2), zw(_zw) { }
	public:
		void inc() { ++i1; ++i2; }
		bool equals(const const_iterator_local& that) const noexcept { return (this->i1 == that.i1) || (this->i2 == that.i2); }
		auto get() const { return zw->function(*i1,*i2); } 		
	};

	const_iterator_local begin_local() const { return const_iterator_local(list1.begin(), list2.begin(), this);  }
	const_iterator_local end_local()   const { return const_iterator_local(list1.end(),   list2.end(),   this);  }
};

/*
template<typename List1, typename List2, typename Function>
auto zipWith_(Function&& function, List1&& list1, List2&& list2)
{	return ZippedWith<typename std::remove_reference<List1>::type, typename std::remove_reference<List2>::type,typename std::remove_reference<Function>::type>(
		std::forward<Function>(function), 
		std::forward<List1>(list1), 
		std::forward<List2>(list2)); 
}



template<typename List1, typename List2>
auto zip(const List1& list1, const List2& list2) 
		-> decltype(zipWith(std::function<std::tuple<typename List1::value_type, typename List2::value_type>
			(typename List1::value_type, typename List2::value_type)>
			(std::make_tuple<typename List1::value_type, typename List2::value_type>), list1, list2))
{
	return zipWith(
		std::function<std::tuple<typename List1::value_type, typename List2::value_type>
			(typename List1::value_type, typename List2::value_type)>
		(std::make_tuple<typename List1::value_type, typename List2::value_type>), list1, list2);
}
*/



/**************************************
 * fun::API                           *
 **************************************/
auto zipWith = function<3>([] (auto&& p1, auto&& p2, auto&& p3) { 
	return ZippedWith<
		typename std::remove_reference<decltype(p1)>::type,
		typename std::remove_reference<decltype(p2)>::type,
		typename std::remove_reference<decltype(p3)>::type>
		(	std::forward<decltype(p1)>(p1),
		    std::forward<decltype(p2)>(p2),
			std::forward<decltype(p3)>(p3));
});
auto zip     = function<2>([] (auto&& l1, auto&& l2) { return zipWith([] (auto o1, auto o2) { return std::make_tuple(o1, o2); }, l1, l2); });


}; //namespace fun

#endif
