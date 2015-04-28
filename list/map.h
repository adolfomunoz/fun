#ifndef _FUNCTIONAL_MAP_H_
#define _FUNCTIONAL_MAP_H_

#include "../iterator/const_iterator.h"
#include <type_traits>
#include <utility>
#include <memory>


namespace fun {

template<typename List, typename Function>
class Mapped
{
	std::unique_ptr<List> list; typename List::const_iterator b; typename List::const_iterator e;
	Function function;
	friend class const_iterator;
public:
	Mapped(Function&& _function, List&& _list):
		list(std::make_unique<List>(_list)), b(*list.begin()), e(*list.end()), 
		function(std::forward<Function>(_function)) { }

	Mapped(Function&& _function, const List& _list):
		b(_list.begin()), e(_list.end()), 
		function(std::forward<Function>(_function)) { }

	Mapped(const Function& _function, List&& _list):
		list(std::make_unique<List>(_list)), b(*list.begin()), e(*list.end()), 
		function(_function) { }

	Mapped(const Function& _function, const List& _list):
		b(_list.begin()), e(_list.end()), 
		function(_function) { }

	using value_type = decltype(function(std::declval<typename List::value_type>()));

	class const_iterator : public ConstIteratorFacade<const_iterator>
	{
		friend class Mapped<List,Function>;
		typename List::const_iterator i;
		const Mapped<List,Function>* m;

		const_iterator(const typename List::const_iterator& _i, const Mapped<List,Function>* _m) : i(_i), m(_m) { }
	public:
		void inc() { ++i; }
		bool equals(const const_iterator& that) const       { return this->i == that.i; }
		Mapped<List,Function>::value_type operator*() const { return m->function(*i);   } 		
	};

	const_iterator begin() const { return const_iterator(b, this);  }
	const_iterator end()   const { return const_iterator(e, this);  }
};

template<typename List, typename Function>
auto map_(Function&& function, List&& list)
{	return Mapped<typename std::remove_reference<List>::type, typename std::remove_reference<Function>::type>
		(std::forward<Function>(function), std::forward<List>(list));  }

/**************************************
 * fun::API                           *
 **************************************/
auto map = [] (auto&& p1, auto&& p2) { return map_(p1, p2); };

}; //namespace fun

#endif
