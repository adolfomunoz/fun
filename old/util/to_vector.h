#ifndef _FUNCTIONAL_TO_VECTOR_H_
#define _FUNCTIONAL_TO_VECTOR_H_

#include <vector>

namespace fun {

template<typename List>
std::vector<typename List::value_type> to_vector(const List& l)
{
	std::vector<typename List::value_type> sol;
	for (auto e : l) sol.push_back(e);
	return sol;
}

template<typename T>
const std::vector<T>& to_vector(const std::vector<T>& l) 
{
	return l;
}

template<typename T>
std::vector<T>&& to_vector(std::vector<T>&& l)
{
	return l;
} 

}; //namespace fun

#endif
