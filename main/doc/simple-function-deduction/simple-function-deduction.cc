#include <iostream>
#include <fun.h>

double sqr(double d) { return d*d; }
struct Sqr {
    double operator()(double d) const { return d*d; }	
};
int main(int argc, char** argv) {
	auto fun_sqr1 = fun::function([] (double f) { return f*f; });
	auto fun_sqr2 = fun::function(sqr);
	auto fun_sqr3 = fun::function(Sqr());
	auto lam = [] (double f) { return f*f; };
	auto fun_sqr4 = fun::function(lam);
	Sqr  cob;
	auto fun_sqr5 = fun::function(cob);

	std::cout<<"fun_sqr :: "<<fun::typeinfo<decltype(fun_sqr1)>::name()<<std::endl;

	std::cout<<fun_sqr1(2)<<" "<<
		   fun_sqr2(2)<<" "<<
		   fun_sqr3(2)<<" "<<
		   fun_sqr4(2)<<" "<<
		   fun_sqr5(2)<<std::endl;
}
