#ifndef _FUNCTIONAL_TO_LIST_H_
#define _FUNCTIONAL_TO_LIST_H_

#include <list>

namespace fun {

template<typename List>
std::list<typename List::value_type> to_list(const List& l)
{
	std::list<typename List::value_type> sol;
	for (auto e : l) sol.push_back(e);
	return sol;
}

template<typename T>
const std::list<T>& to_list(const std::list<T>& l) 
{
	return l;
}

template<typename T>
std::list<T>&& to_list(std::list<T>&& l)
{
	return l;
} 

}; //namespace fun

#endif
