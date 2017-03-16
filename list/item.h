#ifndef _FUNCTIONAL_LIST_ITEM_H_
#define _FUNCTIONAL_LIST_ITEM_H_

#include <utility>
#include <memory>
#include "../function/function.h"
#include "drop.h"

namespace fun {

/**
 * We avoid exceptions nor anything similar. Watch out for "head" or "rest" of empty list (segmentation fault)
 */
template<typename List>
typename List::value_type head_(const List& l)
{
    auto i = l.begin();
    return (*i);
};

template<typename List>
unsigned int length_(const List& l)
{   
    unsigned int size = 0;
    for (auto i = l.begin(); i!=l.end();++i) ++size; 
    return size;
}

template<typename List>
bool null_(const List& l)
{   return l.begin() == l.end();  }

template<typename List>
bool elem_(const typename List::value_type& x, const List& l)
{
    for (auto e : l) if (e==x) return true;
    return false;
}


/**************************************
 * fun::API                           *
 **************************************/
auto head   = function<1>([] (auto&& l)           { return head_(l);   });
auto rest   = fun::drop(1); //Seems to be the best implementation
auto length = function<1>([] (auto&& l)           { return length_(l); });
auto elem   = function<2>([] (auto&& x, auto&& l) { return elem_(x,l); });
auto null   = function<1>([] (auto&& l)           { return null_(l);   });

};

#endif
