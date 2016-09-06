#include "../../fun.h"
#include <iostream>

using fun::_;

int main(int argc, char** argv)
{
	//Example 1
	//Checks if an integer is multiple of another one.
	auto is_multiple_of	= fun::function<2>([] (int a, int b) { return (a%b)==0; });
	if (is_multiple_of(14,7)) std::cout<<"14 is multiple of 7"<<std::endl;	

	//The same, but taking advantage of currying
	auto is_multiple_of_c	= fun::function<1>([] (int a) { return (_==0) * (a%_); });
	if (is_multiple_of_c(14,7)) std::cout<<"14 is multiple of 7"<<std::endl;
	// instead of is_multiple_of(14)(7)	
}
