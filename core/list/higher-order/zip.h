#pragma once

#include "../../function/function.h"
#include "../iterable-list.h"
#include "../type.h"
#include <type_traits>
#include <tuple>
#include <functional>
#include <utility>

namespace fun {

template<typename Function, typename List1, typename List2>
class ZippedWith : public IterableListImpl<ZippedWith<Function,List1,List2>,decltype(std::declval<Function>()(std::declval<typename List1::value_type>(), std::declval<typename List2::value_type>()))>
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

	using value_type= typename IterableListImpl<ZippedWith<Function,List1,List2>,decltype(std::declval<Function>()(std::declval<typename List1::value_type>(), std::declval<typename List2::value_type>()))>::value_type;

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


template<typename Function, typename List1, typename List2>
auto zipWith_(Function&& function, List1&& list1, List2&& list2)
{	return ZippedWith<typename std::remove_reference<Function>::type,typename std::remove_reference<List1>::type, typename std::remove_reference<List2>::type>(
		std::forward<Function>(function), 
		std::forward<List1>(list1), 
		std::forward<List2>(list2)); 
}




template<typename List1, typename List2>
auto zip_(List1&& list1, List2&& list2) {
	return zipWith_([] (auto&& o1, auto&& o2) { return std::tuple<typename std::remove_cvref_t<List1>::value_type, typename std::remove_cvref_t<List2>::value_type>(o1,o2); }, list1, list2);
}




/**************************************
 * fun::API                           *
 **************************************/
auto zipWith = function<type<Function,generic::a, generic::b, generic::c>, 
     type<List,generic::a>, type<List,generic::b>, type<List, generic::c>>([] (auto&& p1, auto&& p2, auto&& p3) { return zipWith_(p1,p2,p3); });

auto zip     = function<type<List,generic::a>, type<List,generic::b>,type<List,type<Tuple,generic::a,generic::b>>>([] (auto&& l1, auto&& l2) { return zip_(l1, l2); });


}; //namespace fun
