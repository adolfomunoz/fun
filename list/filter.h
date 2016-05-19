#ifndef _FUNCTIONAL_FILTER_H_
#define _FUNCTIONAL_FILTER_H_

#include "../iterator/const_iterator.h"
#include "../function/function.h"
#include <utility>
#include <type_traits>

namespace fun {

template<typename List, typename Predicate>
class Filtered
{
	std::unique_ptr<List> list; typename List::const_iterator b; typename List::const_iterator e;
	Predicate predicate;
	friend class const_iterator;
public:
	Filtered(Predicate&& _predicate, List&& _list):
		list(std::make_unique<List>(_list)), b(*list.begin()), e(*list.end()),
		predicate(std::forward<Predicate>(_predicate)) { }

	Filtered(Predicate&& _predicate, const List& _list):
		b(_list.begin()), e(_list.end()),
		predicate(std::forward<Predicate>(_predicate)) { }

	Filtered(const Predicate& _predicate, List&& _list):
		list(std::make_unique<List>(_list)), b(*list.begin()), e(*list.end()),
		predicate(_predicate) { }

	Filtered(const Predicate& _predicate, const List& _list):
		b(_list.begin()), e(_list.end()),
		predicate(_predicate) { }

	class const_iterator : public ConstIteratorFacade<const_iterator>
	{
		friend class Filtered<List,Predicate>;
		typename List::const_iterator i;
		const Filtered<List,Predicate>& f;

		void advance() { while( (i!=f.e) && (!f.predicate(*i)) ) ++i; }

		const_iterator(const typename List::const_iterator& _i, const Filtered<List,Predicate>& _f) : i(_i), f(_f) { advance(); }
	public:
		void inc() { ++i; advance(); }
		bool equals(const const_iterator& that) const { return this->i == that.i; }
		typename List::value_type operator*() const { return (*i); } 		
	};

	const_iterator begin() const { return const_iterator(b, *this);  }
	const_iterator end()   const { return const_iterator(e, *this); }

	using value_type = typename List::value_type;
};

template<typename List, typename Predicate>
auto filter_(Predicate&& predicate, List&& list)
{	return Filtered<typename std::remove_reference<List>::type,typename std::remove_reference<Predicate>::type>
		(std::forward<Predicate>(predicate), std::forward<List>(list));  }

/**************************************
 * fun::API                           *
 **************************************/
auto filter = function<2>([] (auto&& p1, auto&& p2) { return filter_(p1, p2); });


}; //namespace fun

#endif
