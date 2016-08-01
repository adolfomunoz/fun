#include "../../fun.h"
#include <iostream>

using fun::_;

int main(int argc, char** argv)
{
	//Example 1
	auto is_multiple_of_three = (_==0) * (_%3);
	//Equivalent:
	//auto is_multiple_of_three = [] (int n) { return (n%3)==0; }
	if (is_multiple_of_three(33)) std::cout<<"33 is multiple of 3"<<std::endl; 
	else std::cout<<"33 is not multiple of 3"<<std::endl;
	if (is_multiple_of_three(71)) std::cout<<"71 is multiple of 3"<<std::endl; 
	else std::cout<<"71 is not multiple of 3"<<std::endl;
}
