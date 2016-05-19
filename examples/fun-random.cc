#include "../fun.h"
#include <iostream>
#include <limits>

int main(int argc, char** argv)
{
	unsigned long seed = 5;
	auto randoms_of_randoms = fun::map(fun::randoms,fun::randomSeeds(seed));
	for (auto rs : fun::take(20,randoms_of_randoms)) { 
		for (auto e : fun::take(20, rs)) std::cout<<e<<" ";
		std::cout<<std::endl;
	}
}
