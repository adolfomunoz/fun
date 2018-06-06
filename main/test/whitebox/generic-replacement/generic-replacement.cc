#include <fun.h>
#include <iostream>

int main(int argc, char** argv) {
	using replacement = fun::generic_replacement_t<1, double, fun::generic_replacement_t<3,int>>;
	std::cout<<"Replacement : "<<fun::typeinfo<replacement>::name()<<std::endl;

	using type = fun::type<fun::generic::b, double, fun::generic::a, fun::generic::d>;
	std::cout<<"Type        : "<<fun::typeinfo<type>::name()<<std::endl;

	using type = fun::type<fun::generic::b, double, fun::generic::a, fun::generic::d>;
	std::cout<<"New Type    : "<<fun::typeinfo<fun::apply_replacements_t<replacement,type>>::name()<<std::endl;	
}
