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
	auto fl = fun::filter([] (int i) { return (i%2)==0; }, l);
	std::cout<<fl<<std::endl;
	//fl is [2,4]
	}

	{
	//Example 2
	auto l = fun::range(1);
	std::cout<<fun::take(5,l)<<std::endl;
	//l is [1,2,3,4,5,...]
	auto fl = fun::filter(_>3,l);
	std::cout<<fun::take(5,fl)<<std::endl;
	//fl is [4,5,6,7,8,...]
	}

	{
	//Example 3
	auto multiples_of_seven = fun::filter([] (int i) { return (i%7)==0; });
	//multiples_of_seven is a function that gets the multiples of seven of a list
	auto fl = multiples_of_seven(fun::range(0,20));
	std::cout<<fl<<std::endl;
	//fl is [0,7,14]
	}
}
