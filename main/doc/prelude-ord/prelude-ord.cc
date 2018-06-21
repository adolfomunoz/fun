#include <iostream>
#include <fun.h>

using namespace fun;
struct Dummy { };
int main(int argc, char** argv) {
	//max (Ord a) => a -> a -> a
	//Maximum between two values.
	std::cout<<"max(5,3) = "<<max(5,3)<<std::endl;
	//This does not compile, does not satisfy Ord
	//std::cout<<max(Dummy(),Dummy())<<std::endl;
	
	//min (Ord a) => a -> a -> a
	//Minimum between two values.
	std::cout<<"min(5.5,3.3) = "<<min(5.5,3.3)<<std::endl;
}
