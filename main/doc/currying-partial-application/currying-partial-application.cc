#include <iostream>
#include <fun.h>

int main(int argc, char** argv) {
	auto div      = fun::function<int,int,int>([] (int a, int b) { return a/b; });
	auto div_auto = fun::function([] (int a, int b) { return a/b; });

	auto div128 = div(128);
	auto div128_auto = div_auto(128);

	std::cout<<div128(16)<<" "<<div128_auto(16)<<std::endl;
	
	auto choose = fun::function([] (bool cond, int a, int b) { return cond?a:b; });

	auto constant_int = choose(true,3);
	auto id_int = choose(false,3);
	
	std::cout<<constant_int(5)<<" "<<id_int(5)<<std::endl;
}
