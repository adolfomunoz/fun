#include "../../fun.h"
#include <iostream>

using fun::_;

int main(int argc, char** argv)
{
	{
	//Example 1
	auto l = fun::range(1,5);
	std::cout<<l<<std::endl;
	//l is [1,2,3,4,5]
	auto ml = fun::map(1+_,l);
	std::cout<<ml<<std::endl;	
	//ml is [2,3,4,5,6]
	}

	{
	//Example 2
	auto l = fun::range(1);
	std::cout<<fun::take(5,l)<<std::endl;
	//l is [1,2,3,4,5,...]
	auto ml = fun::map(2*_,l);
	std::cout<<fun::take(5,ml)<<std::endl;
	//ml is [2,4,6,8,10,...]
	}

	{
	//Example 3
	auto square_list = fun::map([] (int i) { return i*i; });
	//square_list is a function that squares all elements on a list
	auto ml = square_list(fun::range(1,5));
	std::cout<<ml<<std::endl;
	//ml is [1,4,9,16,25]
	}
}
