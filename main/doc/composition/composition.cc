#include <fun.h>
#include <iostream>

int main(int argc, char** argv) {
	auto atod = fun::function<double, const char*>(
		[] (const char* s) { return std::atof(s); });
	auto sqr = fun::function<double, double>([] (double d) { return d*d; });
	auto comp = sqr*atod; //Function composition
	std::cout<<comp("2.5")<<std::endl;
}