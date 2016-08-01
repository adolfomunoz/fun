#ifndef _FUNCTIONAL_CONCATENATE_H_
#define _FUNCTIONAL_CONCATENATE_H_

#include "../list-core/forward-list.h"
#include <type_traits>
#include <tuple>
#include <functional>
#include <utility>
#include <memory>

namespace fun {

template<typename List1, typename List2>
class Concatenated : public ForwardListImpl<Concatenated<List1, List2>,typename List1::value_type>
{
	static_assert(std::is_same<typename List1::value_type, typename List2::value_type>::value,
		"When concatenating lists, both lists must be of the same type.");

	std::shared_ptr<List1> list1; typename List1::const_iterator begin1; typename List1::const_iterator end1;
	std::shared_ptr<List2> list2; typename List2::const_iterator begin2; typename List2::const_iterator end2;
	friend class const_iterator;
public:
	Concatenated(List1&& _list1, List2&& _list2):
		list1(std::make_shared(_list1)), begin1(*list1.begin()), end1(*list1.end()), 
		list2(std::make_shared(_list2)), begin2(*list2.begin()), end2(*list2.end())  { }

	Concatenated(const List1& _list1, List2&& _list2):
		begin1(_list1.begin()), end1(_list1.end()), 
		list2(std::make_shared(_list2)), begin2(*list2.begin()), end2(*list2.end()) { }

	Concatenated(List1&& _list1, const List2& _list2):
		list1(std::make_shared(_list1)), begin1(*list1.begin()), end1(*list1.end()), 
		begin2(_list2.begin()), end2(_list2.end()) { }

	Concatenated(const List1& _list1, const List2& _list2):
		begin1(_list1.begin()), end1(_list1.end()), 
		begin2(_list2.begin()), end2(_list2.end()) { }


	using value_type = typename List1::value_type;

	class const_iterator_local
	{
		friend class Concatenated<List1, List2>;
		typename List1::const_iterator i1; 
		typename List2::const_iterator i2;
		const Concatenated<List1, List2>* cd;

	public:
		void inc() { if (i1 != cd->end1) ++i1; else ++i2; }
		bool equals(const const_iterator_local& that) const noexcept { return (this->i1 == that.i1) && (this->i2 == that.i2); }
		Concatenated<List1, List2>::value_type get() const { return (i1 == cd->end1)?*i2:*i1; } 		
		const_iterator_local(const typename List1::const_iterator& _i1, 
			       const typename List2::const_iterator& _i2, 
			const Concatenated<List1, List2>* _cd) : i1(_i1), i2(_i2), cd(_cd) { }
	};

	const_iterator_local begin_local() const { return const_iterator_local(begin1, begin2, this);  }
	const_iterator_local end_local()   const { return const_iterator_local(end1,   end2,   this);  }
};

template<typename List1, typename List2>
auto concatenate_(List1&& list1, List2&& list2)
{	return Concatenated<typename std::remove_reference<List1>::type, typename std::remove_reference<List2>::type>(
		std::forward<List1>(list1), 
		std::forward<List2>(list2)); 
}

template<typename List1, typename List2, typename... Ls>
auto concatenate_(List1&& list1, List2&& list2, Ls&&... ls)
{	return concatenate_(
		Concatenated<typename std::remove_reference<List1>::type, typename std::remove_reference<List2>::type>(
			std::forward<List1>(list1), std::forward<List2>(list2)), std::forward(ls)...); 
}

/**************************************
 * fun::API                           *
 **************************************/
//auto concatenate = [] (auto&&... params) { return concatenate_(params...); };
auto concatenate = [] (auto&& l1, auto&& l2, auto&&... params) { return concatenate_(l1, l2, params...); };
//This works only with lists defined by fun with generic lists (can be std::list, for instance).
template<typename L1, typename L2, typename T>
auto operator+(const ForwardListImpl<L1,T>& l1, const ForwardListImpl<L2,T>& l2) { return concatenate(l1, l2); }
template<typename L1, typename L2, typename T>
auto operator+(const L1& l1, const ForwardListImpl<L2,T>& l2) { return concatenate(l1, l2); }
template<typename L1, typename L2, typename T>
auto operator+(const ForwardListImpl<L1,T>& l1, const L2& l2) { return concatenate(l1, l2); }
template<typename T>
auto operator+(const ForwardList<T>& l1, const ForwardList<T>& l2) { return concatenate(l1, l2); }
template<typename L1, typename T>
auto operator+(const L1& l1, const ForwardList<T>& l2) { return concatenate(l1, l2); }
template<typename L2, typename T>
auto operator+(const ForwardList<T>& l1, const L2& l2) { return concatenate(l1, l2); }






}; //namespace fun

#endif
