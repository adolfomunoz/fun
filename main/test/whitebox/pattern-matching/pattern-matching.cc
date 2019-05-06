#include <fun.h>
#include <iostream>
#include <iomanip>
#include <core/function/pattern-matching.h>

using namespace fun;
int main() {
		auto f1 = function_pattern_matching(fun::pattern(_),[] () { return 6; });
		auto f2 = function_pattern_matching(fun::pattern(1),[] () { return 10; },
											fun::pattern(3),[] () { return 7; },
											fun::pattern(_),[] () { return -1; });
		for (int i = 0;i<=10;++i) std::cout<<std::setw(3)<<i<<" -> "<<std::setw(3)<<f1(i)<<" "<<std::setw(3)<<f2(i)<<std::endl;
		auto my_and = function_pattern_matching(fun::pattern(false,_),[] () { return false; },
											    fun::pattern(true,_x),[] (bool x) { return x; });
												
		std::cout<<"\t true\t false"<<std::endl;
		std::cout<<"true\t"<<my_and(true,true)<<"\t"<<my_and(true,false)<<std::endl;
		std::cout<<"false\t"<<my_and(false,true)<<"\t"<<my_and(false,false)<<std::endl;
	
		auto f3 = function_pattern_matching(fun::pattern(1),[] () { return 10; },
											fun::pattern(3),[] () { return 7; });
		std::cout<<f3(2)<<std::endl; //This generates an exception

}