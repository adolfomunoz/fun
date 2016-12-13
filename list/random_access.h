#ifndef _FUNCTIONAL_CONCATENATE_H_
#define _FUNCTIONAL_CONCATENATE_H_

#include "../list-core/forward-list.h"
#include "drop.h"
#include "item.h"
#include <array>
#include <vector>
#include <list>

namespace fun {

/**************************************
 * fun::API                           *
 **************************************/
template<typename L1, typename T>
typename L1::value_type operator||(const ForwardListImpl<L1,T>& l1, unsigned long i)
{	return first(drop(l1,i));	}

template<typename T>
typename ForwardList<T>::value_type operator||(const ForwardList<T>& l1, unsigned long i)
{	return first(drop(l1,i));	}

template<typename T>
typename std::list<T>::value_type operator||(const std::list<T>& l1, unsigned long i)
{	return first(drop(l1,i));	}

template<typename T, unsigned long N>
typename std::array<T,N>::value_type operator||(const std::array<T,N>& l1, unsigned long i)
{	return l1[i]; }

template<typename T>
typename std::vector<T>::value_type operator||(const std::vector<T>& l1, unsigned long i)
{	return l1[i]; }

}; //namespace fun

#endif
