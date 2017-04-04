#ifndef _FUNCTIONAL_LIST_CYCLE_H_
#define _FUNCTIONAL_LIST_CYCLE_H_

#include "../iterator/const_iterator.h"
#include <memory>

//Maybe we will have new implementations as we expand the API but right now this is
//the only way
namespace fun {

template<typename List>
class Cycle : public ForwardListImpl<Cycle<List>, typename List::value_type>
{
    List l; 
public:
	using value_type = typename List::value_type;
	
    Cycle(const List& _l) : l(l) { } 
    Cycle(List&& _l)      : l(l) { }

    class const_iterator_local
    {
	    typename List::const_iterator i;
		const List& l;


	public:
		void inc() { ++i; if (i==l.end()) i = l.begin(); }
		bool equals(const const_iterator_local& that) const noexcept 
		{ 	return (this->i == that.i); 	}
		auto get() const { return (*i);   } 		
		const_iterator_local(const typename List::const_iterator& i, const List& l) : 
		    i(i), l(l) { }
    };

    const_iterator_local begin_local() const { return const_iterator_local(l.begin(), l); }
    const_iterator_local end_local()   const { return const_iterator_local(l.end(), l); }
};

template<typename List>
auto cycle_(List&& l) 
{   return Cycle<typename std::remove_reference<List>::type>(std::forward<List>(l)); }



/**************************************
 * fun::API                           *
 **************************************/
auto cycle   = [] (auto&& l) { return cycle_(l);   };

};

#endif
