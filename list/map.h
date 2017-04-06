#ifndef _FUNCTIONAL_MAP_H_
#define _FUNCTIONAL_MAP_H_

#include "../function/function.h"
#include "../list-core/forward-list.h"
#include "explore.h"
#include <type_traits>
#include <utility>
#include <memory>


namespace fun {

template<typename Function, typename List>
class Mapped : public ForwardListImpl<Mapped<Function,List>,decltype(std::declval<Function>()(std::declval<typename List::value_type>()))>
{
private:
	List list;
	Function function;

public:
	using value_type = typename ForwardListImpl<Mapped<List,Function>,decltype(std::declval<Function>()(std::declval<typename List::value_type>()))>::value_type;

	class const_iterator_local {
	private:
		typename List::const_iterator i;
		const Function& f;
	public:
	    void inc() { ++i; }
	    auto get() const { return f(*i); }
		bool equals(const const_iterator_local& that) const noexcept 
		{ 	return this->i==that.i; 	}
		const_iterator_local(const typename List::const_iterator& i, 
							 const Function& f) : i(i), f(f) { }
	};

	const_iterator_local begin_local() const { return const_iterator_local(list.begin(), function);  }
	const_iterator_local end_local()   const { return const_iterator_local(list.end(), function);  }

	Mapped(Function&& f, List&& l): list(std::forward<List>(l)), function(std::forward<Function>(f)) { 
		//std::cerr<<"map moves list"<<std::endl;   
	}
	Mapped(Function&& f, const List& l): list(l), function(std::forward<Function>(f)) { 
		//std::cerr<<"map copies list"<<std::endl;   
	}
	Mapped(const Function& f, List&& l): list(std::forward<List>(l)), function(f) {
		//std::cerr<<"map moves list"<<std::endl;   
	}
	Mapped(const Function& f, const List& l): list(l), function(f) { 
		//std::cerr<<"map copies list"<<std::endl;   
	}
};

/*
template<typename List, typename Function>
auto map_(Function&& function, List&& list)
{	return Mapped<typename std::remove_reference<List>::type, typename std::remove_reference<Function>::type>
		(std::forward<Function>(function), std::forward<List>(list));  }
*/		

/**************************************
 * fun::API                           *
 **************************************/
auto map   = function<2>([] (auto&& p1, auto&& p2) { 
	return Mapped<typename std::remove_reference<decltype(p1)>::type, typename std::remove_reference<decltype(p2)>::type>(
		std::forward<decltype(p1)>(p1), std::forward<decltype(p2)>(p2)); 
});

//Does not work because explore does not work propperly
auto map_2 = function<2>([] (auto&& f, auto&& l) {
	return explore([f] (auto& i) { return f(*(i++)); },l);
});
}; //namespace fun

#endif
