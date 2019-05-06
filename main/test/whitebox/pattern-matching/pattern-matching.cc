#include <fun.h>
#include <iostream>
#include <iomanip>
#include <core/function/pattern-matching.h>

using namespace fun;
int main() {
		auto f1 = fun::function_pattern_matching<int,int>(fun::pattern(_),fun::value(6));
		auto f2 = fun::function_pattern_matching<int,int>(fun::pattern(1),fun::value(10),
						    		  fun::pattern(3),fun::value(7),
						                  fun::pattern(_),fun::value(-1));
		auto f3 = function_pattern_matching<int,int>(fun::pattern(_x), fun::id); 
		for (int i = 0;i<=10;++i) std::cout<<std::setw(3)<<i<<" -> "<<std::setw(3)<<f1(i)<<" "<<std::setw(3)<<f2(i)<<" "<<std::setw(3)<<f3(i)<<std::endl;

		
		auto my_and = function_pattern_matching<bool,bool,bool>(fun::pattern(false,_),fun::value(false),
						                        fun::pattern(true,_x),fun::id);
												
		std::cout<<"\t true\t false"<<std::endl;
		std::cout<<"true\t"<<my_and(true,true)<<"\t"<<my_and(true,false)<<std::endl;
		std::cout<<"false\t"<<my_and(false,true)<<"\t"<<my_and(false,false)<<std::endl; 
	
		auto f4 = function_pattern_matching<int,int>(fun::pattern(1),fun::value(10),
						    fun::pattern(3),fun::value(7)); 
		try {
			std::cout<<f4(2)<<std::endl; //This generates an exception
		} catch(std::exception& e) {
			std::cout<<"Exception : "<<e.what()<<std::endl;
		}

}
