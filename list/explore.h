#ifndef _FUNCTIONAL_EXPLORE_H_
#define _FUNCTIONAL_EXPLORE_H_

#include "../function/function.h"
#include "../list-core/forward-list.h"
#include "../iterator/const_iterator.h"
#include <type_traits>
#include <utility>
#include <memory>

namespace fun {

//The function has only one parameter: an iterator. Every time it is called it moves the iterator as needed and returns a value.
template<typename List, typename Function>
class Explored : public ForwardListImpl<Explored<List,Function>,decltype(std::declval<Function>()(std::declval<typename List::const_iterator&>()))>
{
private:
	std::shared_ptr<List> list; typename List::const_iterator b; typename List::const_iterator e;
	Function function;

public:
	using value_type =typename ForwardListImpl<Explored<List,Function>,decltype(std::declval<Function>()(std::declval<typename List::const_iterator&>()))>::value_type;

	class const_iterator_local {
	private:
		typename List::const_iterator i;
		const Explored<List,Function>* m;
		Explored<List,Function>::value_type v;
	public:
	        void inc() { v=m->function(i); }
	        auto get() const { return v; }
		bool equals(const const_iterator_local& that) const noexcept { return this->i==that.i; }
		const_iterator_local(const typename List::const_iterator& _i, const Explored<List,Function>* _m) : i(_i), m(_m) { v=m->function(i); }
		friend class Explored<List,Function>;
	};

	const_iterator_local begin_local() const { return const_iterator_local(b, this);  }
	const_iterator_local end_local()   const { return const_iterator_local(e, this);  }

	Explored(Function&& _function, List&& _list):
		list(std::make_shared<List>(_list)), b(*list.begin()), e(*list.end()), 
		function(std::forward<Function>(_function)) { }

	Explored(Function&& _function, const List& _list):
		b(_list.begin()), e(_list.end()), 
		function(std::forward<Function>(_function)) { }

	Explored(const Function& _function, List&& _list):
		list(std::make_shared<List>(_list)), b(*list.begin()), e(*list.end()), 
		function(_function) { }

	Explored(const Function& _function, const List& _list):
		b(_list.begin()), e(_list.end()), 
		function(_function) { }


};


template<typename List, typename Function>
auto explore_(Function&& function, List&& list)
{	return Explored<typename std::remove_reference<List>::type, typename std::remove_reference<Function>::type>
		(std::forward<Function>(function), std::forward<List>(list));  }


/**************************************
 * fun::API                           *
 **************************************/
auto explore = function<2>([] (auto&& p1, auto&& p2) { return explore_(p1, p2); });


}; //namespace fun

#endif
