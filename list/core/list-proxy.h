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
	typename List::const_iterator e; //FOR SOME REASON THE ITERATOR TO THE END CHANGES AFTER THE CONSTRUCTOR AND BEFORE INVOKING BEGIN

public:
	using value_type = typename List::value_type;
	
	void pop_front() { ++b; }
	
	class const_iterator_local {
	private:
		typename List::const_iterator i;
	public:
	    void inc() { 
//			std::cerr<<(*(this->i))<<" -> ";
			++i; 
//			std::cerr<<(*(this->i))<<std::endl;
	    }

	    auto get() const { 
//		   std::cerr<<" ("<<(*i)<<") "; 
		   return (*i); 
	    }
	    
	    bool equals(const const_iterator_local& that) const noexcept {
//			std::cerr<<(this->i._M_node)<<" == "<<(that.i._M_node)<<" ";
			return ((this->i) == (that.i)); 
	    }
	    
	    const_iterator_local(const typename List::const_iterator& _i) : i(_i) { }
	};

	const_iterator_local begin_local() const { return const_iterator_local(b);  }
	const_iterator_local end_local()   const { return const_iterator_local(e);  }

	ListProxy(ListProxy<List>&& l) : list(std::move(l.list)), b(list.begin()), e(list.end()) { }
	ListProxy(List&& l) : list(std::forward<List>(l)), b(list.begin()), e(list.end())        { } 
	
        //Watch out, this actually copies stuff
	ListProxy(const ListProxy<List>& l) : list(l.list), b(list.begin()), e(list.end())       { }
	ListProxy(const List& l) : list(l), b(list.begin()), e(list.end())                       { }
	
	//For list references
	ListProxy(typename List::const_iterator& b, typename List::const_iterator& e) : b(b), e(e) { } 
};

template<typename List>
auto list_proxy(List&& l) 
{	return ListProxy<typename std::remove_reference<List>::type>(std::forward<List>(l)); }

template<typename List>
auto list_ref(const List& l) 
{	auto b = l.begin(); auto e = l.end();
	return ListProxy<typename std::remove_reference<List>::type>(b, e);    }





};


#endif
