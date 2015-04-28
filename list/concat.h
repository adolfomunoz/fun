#ifndef _FUNCTIONAL_CONCAT_H_
#define _FUNCTIONAL_CONCAT_H_

#include <list>

namespace fun {

//This will stay until we find a way of having polimorphic lists (should be doable but not now)
template<typename List>
std::list<typename List::value_type::value_type> concat_(const List& list_of_lists)
{
	std::list<typename List::value_type::value_type> sol;
	for (auto list : list_of_lists)
		for (auto elem : list)
			sol.push_back(elem);
	return sol;
}

/**************************************
 * fun::API                           *
 **************************************/
//This will not happen until we have polymorphic lists
//auto concat  = curry(foldl1, concatenate);
//We use this naive version instead
auto concat = [] (auto l) { return concat_(l); };


}; //namespace fun

#endif
