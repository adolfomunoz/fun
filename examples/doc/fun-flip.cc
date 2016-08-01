#include "../../fun.h"
#include <iostream>

using fun::_;

int main(int argc, char** argv)
{
	//Example 1
	std::cout<<fun::pow(2,5)<<std::endl;
	//Outputs 32
	
	auto flipped_pow = fun::flip(fun::pow);
	std::cout<<flipped_pow(2,5)<<std::endl;
	//Outputs 25, as if the parameters of fun::pow were exchanged
	
	//Currying, we omit the second parameter of the flipped function
	auto cube = fun::flip(fun::pow)(3);

	std::cout<<cube(5)<<std::endl;
	//Outputs 125
	std::cout<<cube(3)<<std::endl;
	//Outputs 27
}
