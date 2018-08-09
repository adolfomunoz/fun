#include <iostream>
#include <fun.h>

using namespace fun;
using namespace fun::generic;

#define SHOW(x) std::cout<<#x " = "<<x<<std::endl;
#define SHOWTYPE(x) std::cout<<"Type of " #x " = "<<typeinfo<decltype(x)>::name()<<std::endl;

int main(int argc, char** argv) {
	auto fact = fun::function_recursive<classes<Integral, a>,a,a>(
		[] (const auto& self, const auto& x)  { 
			return (x<=0?1:x*self(x-1));
		}
	);
	
	SHOWTYPE(fact);
	SHOWTYPE(fact(5));
	SHOW(fact(5));
	SHOWTYPE(fact((long int)10));
	SHOW(fact((long int)10));
}
