#ifndef _FUNCTIONAL_FOLD_H_
#define _FUNCTIONAL_FOLD_H_

#include "item.h"

namespace fun {

template<typename List, typename BinaryFunction, typename ElementType>
ElementType foldl_(const BinaryFunction& f, const ElementType& e, const List& list)
{
    ElementType sol = e;
    for (auto x : list) sol = f(sol,x);
    return sol;  
}

/**
 * Should never be called
 **/
template<typename Iterator, typename BinaryFunction, typename ElementType>
ElementType foldr__(const BinaryFunction& f, const ElementType& e, const Iterator& begin, const Iterator& end)
{
    if (begin == end) return e;
    else {
	    auto next = begin; ++next;
	    return f(*begin,foldr__(f, e, next, end));
    }
} 

/**
 * Should never be called
 **/
template<typename Iterator, typename BinaryFunction, typename ElementType>
ElementType foldr1__(const BinaryFunction& f, const Iterator& begin, const Iterator& end)
{
    auto next = begin; ++next;
    if (next == end) return (*begin);
    else return foldr1__(f, next, end);
}

/**
 * Foldr uses recursivity. Con: it is slower. Pro: it enables short-circuited evaluation, so it could work with infinite lists.
 */
template<typename List, typename BinaryFunction, typename ElementType>
ElementType foldr_(const BinaryFunction& f, const ElementType& e, const List& list)
{   return foldr__(f, e, list.begin(), list.end());			      }

/**
 * Foldr uses recursivity. Con: it is slower. Pro: it enables short-circuited evaluation, so it could work with infinite lists.
 */
template<typename List, typename BinaryFunction, typename ElementType>
ElementType foldr1_(const BinaryFunction& f, const List& list)
{   return foldr1__(f, list.begin(), list.end());			      }

/**
 * We implement this to consider short-circuited evaluation
 **/
template<typename List>
bool andl_(const List& list)
{
   for (auto x : list) if (!x) return false;
   return true;
};

/**
 * We implement this to consider short-circuited evaluation
 **/
template<typename List>
bool orl_(const List& list)
{
   for (auto x : list) if (x) return true;
   return false;
};

template<typename List, typename Predicate>
bool all_(const Predicate& p, const List& list)
{
   for (auto x : list) if (!p(x)) return false;
   return true;
};

template<typename List, typename Predicate>
bool any_(const Predicate& p, const List& list)
{
   for (auto x : list) if (p(x)) return true;
   return false;
};

/**************************************
 * fun::API                           *
 **************************************/
auto foldl   = [] (auto&& f, auto&& e, auto&& list) { return foldl_(f,e,list);                };
auto foldl1  = [] (auto&& f, auto&& list)           { return foldl_(f,head(list),rest(list)); };
auto foldr   = [] (auto&& f, auto&& e, auto&& list) { return foldr_(f,e,list);                };
auto foldr1  = [] (auto&& f, auto&& list)           { return foldr1_(f,list);                 };
auto sum     = [] (auto list)			    { return foldl_([] (auto o1, auto o2) { return o1  + o2; }, (typename decltype(list)::value_type)(0), list); };	
auto product = [] (auto list)			    { return foldl_([] (auto o1, auto o2) { return o1  * o2; }, (typename decltype(list)::value_type)(1), list); };	
auto andl    = [] (auto list)			    { return andl_(list); };
auto orl     = [] (auto list)			    { return orl_(list);  };
    
};

#endif

