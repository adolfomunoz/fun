#include <iostream>
#include <fun.h>

#define SHOW(x) std::cout<<#x " = "<<x<<std::endl;
using namespace fun;
int main(int argc, char** argv) {
	//div (Integral a) => a -> a
	//Integral division
	SHOW(fun::div(7,3));
	
	//mod (Integral a) => a -> a
	//Rest of integral division	
	SHOW(mod(7,3));
	

	//substract (Integral a) => a -> a -> a
	//flipped substraction
	SHOW(substract(3,7));
	
	//odd (Integral a) => a -> Bool
	SHOW(odd(7));
	
	//even (Integral a) => a -> Bool
	SHOW(even(7));
	
}
