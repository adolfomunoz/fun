#include <iostream>
#include <fun.h>

#define SHOW(x) std::cout<<#x " = "<<x<<std::endl;
using namespace fun;
int main(int argc, char** argv) {
	//abs (Num a) => a -> a
	//Absolute value.
	SHOW(fun::abs(-1));
	SHOW(fun::abs(3.5));

	//signum (Num a) => a -> a
	//-1 if negative, 0 if zero, 1 if positive
	SHOW(signum(-1));
	SHOW(signum(3.5));	

	
}
