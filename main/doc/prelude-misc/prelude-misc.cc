#include <iostream>
#include <fun.h>
#include <complex>

using namespace fun;
int main(int argc, char** argv) {
	//id :: a -> a
	//Identity function
	std::cout<<"id('x') = "<<id('x')<<std::endl;

	//constant :: a -> b -> a
        //constant x is a unary function which evaluates to x for all inputs. (const in Haskell)
	std::cout<<"constant('x',0) = "<<constant('x',0)<<std::endl;

	//It is generally useful with currying
	auto f0 = constant(0); //Always returns 0
	std::cout<<"constant(0)('x') = "<<f0('x')<<std::endl;	
	std::cout<<"constant(0)(3.14159276) = "<<f0(3.14159276)<<std::endl;

	//flip :: (a -> b -> c) -> b -> a -> c
	//flip f takes its (first) two arguments in the reverse order of f.
	std::cout<<"7 \% 3 = "<<7%3<< " | flip(_%_) (3,7) = "<< flip(_%_) (3,7)<<std::endl;
	//flip (and all functions that have another function as parameter) can have parameters which are lambda, c++ functions or callable objects
	std::cout<<"flip(std::polar<float>) (M_PI,1) = "<<flip(std::polar<float>) (M_PI,1)<<std::endl;

	//until :: (a -> Bool) -> (a -> a) -> a -> a Source#
	//until p f yields the result of applying f until p holds
	// --> stupid mcm between 6 and 8
	std::cout<<"until((_==0)*(_%6),(_+8),8) = "<<until((_==0)*(_%6),(_+8),8)<<std::endl;
}
