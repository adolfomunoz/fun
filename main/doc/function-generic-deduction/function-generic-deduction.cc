#include <iostream>
#include <fun.h>
#include <string>

using namespace fun::generic;
int main(int argc, char** argv) {
	auto id       = fun::function<a,a>([] (const auto& i) { return i; });
	auto constant = fun::function<a,b,a>([] (const auto& c, const auto& dummy) { return c; });

	std::cout<<"id :: "<<fun::type<decltype(id)>::name()<<std::endl;
	std::cout<<"constant :: "<<fun::type<decltype(constant)>::name()<<std::endl;

	std::cout<<"id(5) :: "<<fun::type<decltype(id(5))>::name()<<std::endl;
	std::cout<<"constant('a') :: "<<fun::type<decltype(constant('a'))>::name()<<std::endl;

	auto constant_a = constant('a');

	std::cout<<"id(5) = "<<id(5)<<std::endl;
	std::cout<<"(constant('a')) (5) = "<<constant_a(5)<<
		" | (constant('a')) (3.1416) = "<<constant_a(3.1416)<<
		" | (constant('a')) (\"Hola\") = "<<constant_a(std::string("Hola"))<<std::endl;
}
