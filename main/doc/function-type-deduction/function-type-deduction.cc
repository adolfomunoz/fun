#include <iostream>
#include <fun.h>
#include <string>

using namespace fun::generic;
int main(int argc, char** argv) {
	auto flip     = fun::function<fun::type<fun::Function,a,b,c>,b,a,c>([] (const auto& f, const auto& x, const auto& y) { return f(y,x); });
	auto mod      = fun::function([] (int i, int j) { return i % j; });

	std::cout<<"flip :: "<<fun::typeinfo<decltype(flip)>::name()<<std::endl;
	std::cout<<"mod :: "<<fun::typeinfo<decltype(mod)>::name()<<std::endl;

	auto flip_mod = flip(mod);
	std::cout<<"flip(mod) :: "<<fun::typeinfo<decltype(flip_mod)>::name()<<std::endl;
	
	std::cout<<"mod(7,3) = "<<mod(7,3)<<" | flip(mod) (3,7) = "<<flip_mod(3,7)<<std::endl;
	
	auto pow = fun::function(
	 [] (double b, int e) { double p = 1.0; for (int i=0;i<e;++i) p*=b; return p; }
	);
	
	std::cout<<std::endl;
	std::cout<<"flip :: "<<fun::typeinfo<decltype(flip)>::name()<<std::endl;
	std::cout<<"pow :: "<<fun::typeinfo<decltype(pow)>::name()<<std::endl;

	auto flip_pow = flip(pow);
	std::cout<<"flip(pow) :: "<<fun::typeinfo<decltype(flip_pow)>::name()<<std::endl;

	std::cout<<"pow(2.5,3) = "<<pow(2.5,3)<<" | flip(pow) (3,2.5) = "<<flip_pow(3,2.5)<<std::endl;	
}
