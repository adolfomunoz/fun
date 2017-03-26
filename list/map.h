#ifndef _FUNCTIONAL_MAP_H_
#define _FUNCTIONAL_MAP_H_

#include "../function/function.h"
#include "../list-core/forward-list.h"
#include "explore.h"
#include <type_traits>
#include <utility>
#include <memory>


namespace fun {

template<typename List, typename Function>
class Mapped : public ForwardListImpl<Mapped<List,Function>,decltype(std::declval<Function>()(std::declval<typename List::value_type>()))>
{
private:
	std::shared_ptr<List> list; typename List::const_iterator b; typename List::const_iterator e;
	Function function;

public:
	using value_type = typename ForwardListImpl<Mapped<List,Function>,decltype(std::declval<Function>()(std::declval<typename List::value_type>()))>::value_type;

	class const_iterator_local {
	private:
		typename List::const_iterator i;
		const Mapped<List,Function>* m;
	public:
	        void inc() { ++i; }
	        auto get() const { return m->function(*i); }
		bool equals(const const_iterator_local& that) const noexcept { return this->i==that.i; }
		const_iterator_local(const typename List::const_iterator& _i, const Mapped<List,Function>* _m) : i(_i), m(_m) { }
		friend class Mapped<List,Function>;
	};

	const_iterator_local begin_local() const { return const_iterator_local(b, this);  }
	const_iterator_local end_local()   const { return const_iterator_local(e, this);  }

	Mapped(Function&& _function, List&& _list):
		list(std::make_shared<List>(_list)), b(*list.begin()), e(*list.end()), 
		function(std::forward<Function>(_function)) { }

	Mapped(Function&& _function, const List& _list):
		b(_list.begin()), e(_list.end()), 
		function(std::forward<Function>(_function)) { }

	Mapped(const Function& _function, List&& _list):
		list(std::make_shared<List>(_list)), b(*list.begin()), e(*list.end()), 
		function(_function) { }

	Mapped(const Function& _function, const List& _list):
		b(_list.begin()), e(_list.end()), 
		function(_function) { }


};

template<typename List, typename Function>
auto map_(Function&& function, List&& list)
{	return Mapped<typename std::remove_reference<List>::type, typename std::remove_reference<Function>::type>
		(std::forward<Function>(function), std::forward<List>(list));  }

/**************************************
 * fun::API                           *
 **************************************/
auto map   = function<2>([] (auto&& p1, auto&& p2) { return map_(p1, p2); });
auto map_2 = function<2>([] (auto&& f, auto&& l) {
	return explore([f] (auto& i) { std::cerr<<*i<<" "; return f(*(i++)); },l);
});
}; //namespace fun

#endif
