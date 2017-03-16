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
	auto tl = fun::take(3,l);
	std::cout<<tl<<std::endl;	
	//tl is [1,2,3]
	auto dl = fun::drop(3,l);
	std::cout<<dl<<std::endl;	
	//dl is [4,5]
	auto rl = fun::rest(l);
	std::cout<<rl<<std::endl;
	//fun::rest = fun::drop(1);
	}

	{
	//Example 2
	auto l = fun::range(1);
	std::cout<<fun::take(5,l)<<std::endl;
	//l is [1,2,3,4,5,...]
	auto dl = fun::drop(5,l);
	std::cout<<fun::take(5,dl)<<std::endl;
	//dl is [6,7,8,9,10,...]
	}
	
	{
	//Example 3
	auto l = fun::range(1,6);
	std::cout<<l<<std::endl;
	//l is [1,2,3,4,5,6]
	auto tl = fun::takeWhile([] (int i) { return (i%3)!=0; },l);
	std::cout<<tl<<std::endl;	
	//tl is [1,2]
	auto dl = fun::dropWhile([] (int i) { return (i%3)!=0; },l);
	std::cout<<dl<<std::endl;	
	//dl is [3,4,5]
	}

}
