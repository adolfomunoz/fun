#ifndef _FUNCTIONAL_LIST_PROXY_H_
#define _FUNCTIONAL_LIST_PROXY_H_

#include "forward-list.h"

namespace fun
{

template<typename List>
class ListProxy : public ForwardListImpl<ListProxy<List>, typename List::value_type>
{
private:
	//We need shared_ptr instead of unique_ptr because otherwise
	//it is not copyable. For polymorphism we need them to be
	//copyable
	std::shared_ptr<List> list; typename List::const_iterator b; typename List::const_iterator e;

public:
	using value_type = typename List::value_type;

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

	ListProxy(List&& list, const typename List::const_iterator& begin, const typename List::const_iterator& end):
		list(std::make_shared<List>(list)), 
		b(begin), e(end) { }

	ListProxy(List&& list, const typename List::const_iterator& begin) : ListProxy(list, begin, list.end()) { }
	ListProxy(List&& list) : ListProxy(list, list.begin()) { }
	
	//We avoid copy constructor. We have to be careful, though. Maybe we should include copy constructor, I don't know...
	ListProxy(const List& list, const typename List::const_iterator& begin, const typename List::const_iterator& end): 
//		list(std::make_shared<List>(list)), 
		b(begin), e(end) 
	{ 
//		static_assert(true, "Invoking copy constructor for list, which could be potentially huge");
	}

	ListProxy(const List& list, const typename List::const_iterator& begin) : ListProxy(list, begin, list.end()) { }
	ListProxy(const List& list) : ListProxy(list, list.begin()) { }

};

template<typename List, typename Iterator>
auto list_proxy(List&& l, const Iterator& begin, const Iterator& end) 
{	return ListProxy<typename std::remove_reference<List>::type>(std::forward<List>(l), begin, end);	}

template<typename List, typename Iterator>
auto list_proxy(List&& l, const Iterator& begin) 
{	return list_proxy(std::forward<List>(l), begin, l.end());	}

template<typename List>
auto list_proxy(List&& l) 
{	return list_proxy(std::forward<List>(l), l.begin());	}




};


#endif
