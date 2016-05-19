#ifndef _FUNCTIONAL_LIST_SHOW_H_
#define _FUNCTIONAL_LIST_SHOW_H_

#include "../function/function.h"
#include <string>
#include <sstream>

namespace fun {

template<typename ListType>
std::string show_(const ListType& l)
{	
	std::stringstream sstr;
	sstr<<"[";
	bool first = true;
	for (const auto& e : l) {
		if (first) first = false;
		else sstr<<",";
		sstr<<e;
	}
	sstr<<"]";
	return sstr.str();
}

/**************************************
 * fun::API                           *
 **************************************/
auto show = function<1>([] (const auto& l) { return show_(l); });


}; //namespace fun

#endif
