#include <fun.h>
#include <iostream>

double sqr(double d) { return d*d; }
struct Sqr {
    double operator()(double d) const { return d*d; }	
};
int main(int argc, char** argv) {
	auto fun_sqr1 = fun::function<double, double>([] (double f) { return f*f; });
//	auto fun_sqr2 = fun::function<double, double>(sqr);
	auto fun_sqr3 = fun::function<double, double>(Sqr());


	std::cout<<fun_sqr1(2)<<" "<<
		       //fun_sqr2(2)<<" "<<
			   fun_sqr3(2)<<std::endl;
}