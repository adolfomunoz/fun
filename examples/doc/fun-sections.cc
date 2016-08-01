#include "../../fun.h"
#include <iostream>

using fun::_;

int main(int argc, char** argv)
{
	//Example 1
	//Creating section with + infix operator
	auto add_one = _+1;
	//Using the resulting function
	std::cout<<add_one(3)<<std::endl;
	//Outputs 4
	
	//Example 2
	//Creating the two-parameter section with the == infix operator
	auto are_equal = _==_;
	//Using the resulting function
	if (are_equal(3,3))  std::cout<<"3 and 3 are equal"<<std::endl;
	if (!are_equal(3,4)) std::cout<<"3 and 4 are not equal"<<std::endl;
}
