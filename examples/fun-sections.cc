#include "../fun.h"
#include <iostream>
#include <limits>

using fun::_;

int main(int argc, char** argv)
{
	auto data = fun::take(20,fun::randomsIO());
	std::cout<<fun::show(data)<<std::endl;
	std::cout<<fun::show(fun::map(_+1.0,data))<<std::endl;
}
