#include "../../fun.h"
#include <iostream>

using fun::_;

int main(int argc, char** argv)
{
	//Example 1
	
	std::cout<<fun::pow(2,4)<<std::endl;
	//Outputs 16
	
	//We omit the second parameter
	auto power_of_two = fun::pow(2);
	
	std::cout<<power_of_two(3)<<std::endl;
	//Outputs 8
	std::cout<<power_of_two(8)<<std::endl;
	//Outputs 256

	//Example 2
	auto one = fun::constant(1);
	
	std::cout<<one(32)<<std::endl;
	//Outputs 1
	std::cout<<one("what")<<std::endl;
	//Outputs 1	
}
