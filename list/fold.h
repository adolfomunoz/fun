#ifndef _FUNCTIONAL_FOLD_H_
#define _FUNCTIONAL_FOLD_H_

#include "item.h"
#include "../function/function.h"
#include "../function/section.h"
#include "../list-core/forward-list.h"
#include "../list-core/cast.h"

namespace fun {

/*
template<typename List, typename BinaryFunction, typename ListType>
ForwardList<typename ListType::value_type> foldl__(const BinaryFunction& f, const ListType& e, const List& list, std::true_type)
{
	ForwardList<typename ListType::value_type> sol = e;
	for (auto x : list) sol = f(sol,x);    
	return sol;  
}

template<typename List, typename BinaryFunction, typename ElementType>
ElementType foldl__(const BinaryFunction& f, const ElementType& e, const List& list,std::false_type)
{
	ElementType sol = e;
	for (auto x : list) sol = f(sol,x);
	return sol;  
}

template<typename List, typename BinaryFunction, typename ElementType>
auto foldl_(const BinaryFunction& f, const ElementType& e, const List& list) 
{	return foldl__(f,e,list,is_forward_list(e));  }
*/

template<typename List, typename BinaryFunction, typename ElementType>
typename cast<ElementType>::type foldl_(const BinaryFunction& f, const ElementType& e, const List& list)
{	
	typename cast<ElementType>::type sol(e);
//	std::cerr<<"INPUT : "<<sol<<std::endl;
	for (auto x : list) { sol = f(sol,x); /*std::cerr<<x<<" -> "<<sol<<std::endl;*/ }
//	std::cerr<<"OUTPUT: "<<sol<<std::endl;

	return sol;  
}

/**
 * Should never be called directly
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
 * Should never be called directly
 **/
template<typename Iterator, typename BinaryFunction>
auto foldr1__(const BinaryFunction& f, const Iterator& begin, const Iterator& end)
{
    auto next = begin; ++next;
    if (next == end) return (*begin);
    else return foldr1__(f, next, end);
}

/**
 * Foldr uses recursivity. Con: it is slower. Pro: it enables short-circuited evaluation, so it could work with infinite lists.
 * Pro: it does not require copy construction of ElementType
 */
template<typename List, typename BinaryFunction, typename ElementType>
ElementType foldr_(const BinaryFunction& f, const ElementType& e, const List& list)
{   return foldr__(f, e, list.begin(), list.end());			      }

/**
 * Foldr uses recursivity. Con: it is slower. Pro: it enables short-circuited evaluation, so it could work with infinite lists.
 * Pro: it does not require copy construction of ElementType
 */
template<typename List, typename BinaryFunction>
auto foldr1_(const BinaryFunction& f, const List& list)
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
auto foldl   = function<3>([] (auto&& f, auto&& e, const auto& list) { return foldl_(f,e,list);                });
auto foldl1  = function<2>([] (auto&& f, const auto& list)           { return foldl_(f,head(list),rest(list)); });
auto foldr   = function<3>([] (auto&& f, auto&& e, const auto& list) { return foldr_(f,e,list);                });
auto foldr1  = function<2>([] (auto&& f, const auto& list)           { return foldr1_(f,list);                 });
auto sum     = function<1>([] (const auto& list)		     { return foldl_(_+_, (typename std::remove_reference<decltype(list)>::type::value_type)(0), list); });	
auto product = function<1>([] (const auto& list)	   	     { return foldl_(_*_, (typename std::remove_reference<decltype(list)>::type::value_type)(1), list); });	
auto andl    = function<1>([] (const auto& list)		     { return andl_(list); });
auto orl     = function<1>([] (const auto& list)		     { return orl_(list);  });
    
};

#endif

