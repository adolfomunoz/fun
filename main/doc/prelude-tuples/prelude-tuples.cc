#include <iostream>
#include <fun.h>

using namespace fun;
int main(int argc, char** argv) {
	//fst :: (a, b) -> a
	//Extract the first component of a pair.
	std::cout<<"fst(std::tuple(1,'x')) = "<<fst(std::tuple(1,'x'))<<std::endl;
	//snd :: (a, b) -> b
	//Extract the first component of a pair.
	std::cout<<"snd(std::tuple(1,'x')) = "<<snd(std::tuple(1,'x'))<<std::endl;

	//curry :: ((a, b) -> c) -> a -> b -> c 
	//curry converts an uncurried function to a curried function.
	std::cout<<"curry(fst, 1, 'x') = "<<curry(fst, 1, 'x')<<std::endl;

	//uncurry :: (a -> b -> c) -> (a, b) -> c
	//uncurry converts a curried function to a function on pairs.
	std::cout<<"uncurry(_+_,std::tuple(1,2)) = "<<uncurry(_+_,std::tuple(1,2))<<std::endl;
	std::cout<<"uncurry(_%_,std::tuple(id,1)) = "<<uncurry(_%_,std::tuple(id,1))<<std::endl;
}
