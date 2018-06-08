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
}
