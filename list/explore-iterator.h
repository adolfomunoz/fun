#ifndef _FUNCTIONAL_EXPLORE_ITERATOR_H_
#define _FUNCTIONAL_EXPLORE_ITERATOR_H_

#include "../function/function.h"
#include "../list-core/forward-list.h"
#include "../iterator/const_iterator.h"
#include <type_traits>
#include <utility>
#include <memory>

namespace fun {

//Function:
//   - The function has only one parameter: an iterator. Every time it is called it moves the iterator as needed and returns a value.
//Iterator
//   - In the same fashion, the function "explore" takes a function and an iterator and moves the iterator as needed. 
//Important:
//   - It only works with infinite lists, as it is impossible to know how many elements the function is going to take.
//   - This is NOT FUNCTIONAL: it advances the iterator so multiple calls will yield different results.
template<typename Function, typename Iterator>
class ExploredIterator : public ForwardListImpl<ExploredIterator<Function, Iterator>,decltype(std::declval<Function>()(std::declval<Iterator&>()))>
{
private:
	Iterator& i;
	Function function;
public:
	using value_type = typename ForwardListImpl<ExploredIterator<Function, Iterator>,decltype(std::declval<Function>()(std::declval<Iterator&>()))>::value_type;

	class const_iterator_local {
	private:
		Iterator& i; 
		mutable Iterator i_prev;
		const ExploredIterator<Function, Iterator>* m;
	public:
	        void inc() { i = i_prev; }
	        auto get() const { i_prev=i; return m->function(i_prev); }
		const_iterator_local& operator=(const const_iterator_local& that) 
		{	i =that.i; i_prev = that.i_prev; m = that.m;	}
		bool equals(const const_iterator_local& that) const noexcept { return false; }  //It never ends. It crashes. It only works with inifinite lists of iterable elements.
		const_iterator_local(Iterator& _i, const ExploredIterator<Function,Iterator>* _m) : i(_i), i_prev(i), m(_m) { }
		friend class ExploredIterator<Function, Iterator>;
	};
	
	const_iterator_local begin_local() const { return const_iterator_local(i, this);  }
	const_iterator_local end_local()   const { return const_iterator_local(i, this);  }

	ExploredIterator(Function&& _function, Iterator& _i):
		i(_i), 
		function(std::forward<Function>(_function)) { }

	ExploredIterator(const Function& _function, Iterator& _i):
		i(_i),
		function(_function) { }
};


template<typename Function, typename Iterator>
auto explore_iterator_(Function&& function, Iterator& i)
{	return ExploredIterator<typename std::remove_reference<Function>::type, Iterator>
		(std::forward<Function>(function), i);  }


/**************************************
 * fun::API                           *
 **************************************/
auto explore_iterator = function<2>([] (auto&& p1, auto& p2) { return explore_iterator_(p1, p2); });


}; //namespace fun

#endif
