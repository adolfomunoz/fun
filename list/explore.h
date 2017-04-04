#ifndef _FUNCTIONAL_EXPLORE_H_
#define _FUNCTIONAL_EXPLORE_H_

#include "explore-iterator.h"

namespace fun {



//The function has only one parameter: an iterator. Every time it is called it moves the iterator as needed and returns a value.
template<typename List, typename Function>
class Explored : public ForwardListImpl<Explored<List,Function>,decltype(std::declval<Function>()(std::declval<typename List::const_iterator&>()))>
{
private:
	List list;
	Function function;

public:
	using value_type =typename ForwardListImpl<Explored<List,Function>,decltype(std::declval<Function>()(std::declval<typename List::const_iterator&>()))>::value_type;

	class const_iterator_local {
	private:
		typename List::const_iterator i;
		mutable typename List::const_iterator i_prev;
		const Explored<List,Function>* m;
	public:	
		void inc() { i = i_prev; }
	    auto get() const {
//			std::cerr<<"Pre-get : "<<*i<<" , "<<*i_prev<<"\t";
			i_prev = i; auto sol = m->function(i_prev); 
//			std::cerr<<"Post-get: "<<*i<<" , "<<*i_prev<<std::endl;
			return sol;
		}

		bool equals(const const_iterator_local& that) const noexcept { return this->i==that.i; }
		const_iterator_local(const typename List::const_iterator& _i, const Explored<List,Function>* _m) : i(_i), i_prev(i), m(_m) { }
		friend class Explored<List,Function>;
	};

	const_iterator_local begin_local() const { return const_iterator_local(list.begin(), this);  }
	const_iterator_local end_local()   const { return const_iterator_local(list.end(), this);  }

	Explored(Function&& function, List&& list): list(list), function(function) {}
	Explored(Function&& function, const List& list): list(list), function(function) {}
	Explored(const Function& function, List&& list): list(list), function(function) {}
	Explored(const Function& function, const List& list): list(list), function(function) {}


};


template<typename List, typename Function>
auto explore_(Function&& function, List&& list)
{	return Explored<typename std::remove_reference<List>::type, typename std::remove_reference<Function>::type>
		(std::forward<Function>(function), std::forward<List>(list));  }

//This below segfaults
/*
template<typename List, typename Function>
auto explore_(Function&& function, List&& list)
{	
	auto i = list.begin();
	return explore_iterator_(function,i);
}
*/

/**************************************
 * fun::API                           *
 **************************************/
auto explore = function<2>([] (auto&& p1, auto&& p2) { return explore_(p1, p2); });


}; //namespace fun

#endif
