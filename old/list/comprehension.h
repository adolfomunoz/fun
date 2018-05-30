#ifndef _FUNCTIONAL_COMPREHENSION_H_
#define _FUNCTIONAL_COMPREHENSION_H_

//#include "../iterator/const_iterator.h"
#include <type_traits>
#include <tuple>
#include <functional>
#include <utility>
#include <memory>

namespace fun {

/*
template<typename List1, typename List2, typename Function>
class Comprehension
{
	std::unique_ptr<List1> list1; typename List1::const_iterator begin1; typename List1::const_iterator end1;
	std::unique_ptr<List2> list2; typename List2::const_iterator begin2; typename List2::const_iterator end2;
	Function function;
	friend class const_iterator;
public:
	Comprehension(Function&& _function, List1&& _list1, List2&& _list2):
		list1(std::make_unique(_list1)), begin1(*list1.begin()), end1(*list1.end()), 
		list2(std::make_unique(_list2)), begin2(*list2.begin()), end2(*list2.end()),
		function(std::forward<Function>(_function)) { }

	Comprehension(Function&& _function, const List1& _list1, List2&& _list2):
		begin1(_list1.begin()), end1(_list1.end()), 
		list2(std::make_unique(_list2)), begin2(*list2.begin()), end2(*list2.end()),
		function(std::forward<Function>(_function)) { }

	Comprehension(Function&& _function, List1&& _list1, const List2& _list2):
		list1(std::make_unique(_list1)), begin1(*list1.begin()), end1(*list1.end()), 
		begin2(_list2.begin()), end2(_list2.end()),
		function(std::forward<Function>(_function)) { }

	Comprehension(Function&& _function, const List1& _list1, const List2& _list2):
		begin1(_list1.begin()), end1(_list1.end()), 
		begin2(_list2.begin()), end2(_list2.end()),
		function(std::forward<Function>(_function)) { }

	Comprehension(const Function& _function, List1&& _list1, List2&& _list2):
		list1(std::make_unique(_list1)), begin1(*list1.begin()), end1(*list1.end()), 
		list2(std::make_unique(_list2)), begin2(*list2.begin()), end2(*list2.end()),
		function(_function) { }

	Comprehension(const Function& _function, const List1& _list1, List2&& _list2):
		begin1(_list1.begin()), end1(_list1.end()), 
		list2(std::make_unique(_list2)), begin2(*list2.begin()), end2(*list2.end()),
		function(_function) { }

	Comprehension(const Function& _function, List1&& _list1, const List2& _list2):
		list1(std::make_unique(_list1)), begin1(*list1.begin()), end1(*list1.end()), 
		begin2(_list2.begin()), end2(_list2.end()),
		function(_function) { }

	Comprehension(const Function& _function, const List1& _list1, const List2& _list2):
		begin1(_list1.begin()), end1(_list1.end()), 
		begin2(_list2.begin()), end2(_list2.end()),
		function(_function) { }


	using value_type = decltype(function(
			std::declval<typename List1::value_type>(),
			std::declval<typename List2::value_type>()));

	class const_iterator : public ConstIteratorFacade<const_iterator>
	{
		friend class Comprehension<List1, List2, Function>;
		typename List1::const_iterator i1; 
		typename List2::const_iterator i2;
		const Comprehension<List1, List2, Function>* co;

		const_iterator(const typename List1::const_iterator& _i1, 
			       const typename List2::const_iterator& _i2, 
			const Comprehension<List1, List2, Function>* _co) : i1(_i1), i2(_i2), co(_co) { }
	public:
		void inc() { ++i1; if (i1 == co->end1) { i1 = co->begin1; ++i2; } }
		bool equals(const const_iterator& that) const noexcept { return (this->i1 == that.i1) || (this->i2 == that.i2); }
		Comprehension<List1, List2, Function>::value_type operator*() const { return co->function(*i1,*i2); } 		
	};

	const_iterator begin() const { return const_iterator(begin1, begin2, this);  }
	const_iterator end()   const { return const_iterator(end1,   end2,   this);  }
};

template<typename List1, typename List2, typename Function>
auto comprehensionWith_(Function&& function, List1&& list1, List2&& list2)
{	return Comprehension<typename std::remove_reference<List1>::type, typename std::remove_reference<List2>::type,typename std::remove_reference<Function>::type>(
		std::forward<Function>(function), 
		std::forward<List1>(list1), 
		std::forward<List2>(list2)); 
}
*/
/**************************************
 * fun::API                           *
 **************************************/

//auto comprehensionWith = [] (auto&& p1, auto&& p2, auto&& p3) { return comprehensionWith_(p1, p2, p3); };
//auto comprehension     = [] (auto&& l1, auto&& l2)            { return comprehensionWith_([] (auto o1, auto o2) { return std::make_tuple(o1, o2); }, l1, l2); };


}; //namespace fun

#endif
