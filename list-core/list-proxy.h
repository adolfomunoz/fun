#ifndef _FUNCTIONAL_LIST_PROXY_H_
#define _FUNCTIONAL_LIST_PROXY_H_

#include "forward-list.h"

namespace fun
{

template<typename List>
class ListProxy : public ForwardListImpl<ListProxy<List>, typename List::value_type>
{
private:
	//We copy or move. Watch out with huge std::list or std::vector
	List list; 
	typename List::const_iterator b;
	typename List::const_iterator e;

public:
	using value_type = typename List::value_type;
	void pop_front() { ++b; }
	
	class const_iterator_local {
	private:
		typename List::const_iterator i;
	public:
	    void inc() { ++i; }
	    auto get() const { return (*i); }
		bool equals(const const_iterator_local& that) const noexcept { return this->i==that.i; }
		const_iterator_local(const typename List::const_iterator& _i) : i(_i) { }
	};

	const_iterator_local begin_local() const { return const_iterator_local(b);  }
	const_iterator_local end_local()   const { return const_iterator_local(e);  }

	ListProxy(List&& list) : 
		list(list), b(list.begin()), e(list.end()) {}
	
    //Watch out, this actually copies stuff
	ListProxy(const List& list) : 
		list(list), b(list.begin()), e(list.end()) {}
};

template<typename List>
auto list_proxy(List&& l) 
{	return ListProxy<typename std::remove_reference<List>::type>(std::forward<List>(l));  }




};


#endif
