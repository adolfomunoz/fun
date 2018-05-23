#include <fun.h>
#include <iostream>


int main(int argc, char** argv) {
	auto my_function = fun::function<double, double>([] (double f) { return f*f; });
	std::cout<<my_function(2)<<std::endl;
}