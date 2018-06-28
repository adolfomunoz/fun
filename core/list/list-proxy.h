#pragma once

#include "iterable-list.h"
namespace fun
{

template<typename List>
class ListRef : public IterableListImpl<ListRef<List>, typename List::value_type>
{
protected:
	typename List::const_iterator b;
	typename List::const_iterator e; //FOR SOME REASON THE ITERATOR TO THE END CHANGES AFTER THE CONSTRUCTOR AND BEFORE INVOKING BEGIN
	
	ListRef() { } 
public:
	using value_type = typename List::value_type;
	
	// void pop_head() { ++b; }  //Absolute useless for drop (because of copying and returning) so we won't use it	


	class const_iterator_local {
	private:
		typename List::const_iterator i;
	public:
	    void inc() { ++i; }
	    auto get() const { return (*i); }
	    bool equals(const const_iterator_local& that) const noexcept {
			return ((this->i) == (that.i)); 
	    }
	    
	    const_iterator_local(const typename List::const_iterator& _i) : i(_i) { }
	};

	const_iterator_local begin_local() const { return const_iterator_local(b);  }
	const_iterator_local end_local()   const { return const_iterator_local(e);  }

	ListRef(const typename List::const_iterator& b, const typename List::const_iterator& e) : b(b), e(e) { } 
};


template<typename List>
class ListProxy : public IterableListImpl<ListProxy<List>, typename List::value_type>
{
private:
	//We copy or move. Watch out with huge std::list or std::vector
	List list; 
	ListRef<List> ref;

public:
	using value_type = typename List::value_type;
	using const_iterator_local = typename ListRef<List>::const_iterator_local;
	
	//void pop_head() { ref.pop_head(); } //Absolute useless for drop (because of copying and returning) so we won't use it	

	ListProxy(ListProxy<List>&& l) : list(std::move(l.list)), 
		ref(list.begin(), list.end()) { }
	ListProxy(List&& l) : list(std::forward<List>(l)),       
		ref(list.begin(), list.end()) { }

        //Watch out, this actually copies stuff
	ListProxy(const ListProxy<List>& l) : list(l.list), 
		ref(list.begin(), list.end()) { }
	ListProxy(const List& l) : list(l),
		ref(list.begin(), list.end()) { }

	const_iterator_local begin_local() const { return ref.begin_local();  }
	const_iterator_local end_local()   const { return ref.end_local();    }


};

template<typename List>
auto list_proxy(List&& l) 
{	return ListProxy<typename std::remove_reference<List>::type>(std::forward<List>(l)); }

template<typename List>
auto list_ref(const List& l) 
{	auto b = l.begin(); auto e = l.end();
	return ListRef<typename std::remove_reference<List>::type>(b, e);    }





};

