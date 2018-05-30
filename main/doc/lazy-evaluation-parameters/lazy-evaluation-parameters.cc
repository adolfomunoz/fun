#include <iostream>
#include <fun.h>

int main(int argc, char** argv) {
	auto negate   = fun::function([] (int i) { return -i; });
	auto multiply = fun::function([] (int i, int j) { return i*j; });
	auto sum      = fun::function([] (int n1, int n2) { std::cout<<"sum("<<n1<<","<<n2<<")"<<std::endl; int s=0; for(int i=n1; i<=n2; ++i) s+=i; return s; });

	//sum_fast is not evaluated now
	auto negate_sum_fast = negate(sum(0,10)); 
    //sum_slow is not evaluated now	
	auto negate_sum_slow = negate(sum(0,1000000));
	//sum_fast is evaluated now - prints sum(0,10) and then negates its result
	std::cout<<negate_sum_fast<<std::endl;
	//sum_slow is never evaluated because it is never used.
	
	//sum_fast is not evaluated now
	auto multiply_sum_fast = multiply(sum(0,10),2); 
    //sum_slow is not evaluated now	
	auto multiply_sum_slow = multiply(sum(0,1000000),2);
	//sum_fast is evaluated now - prints sum(0,10) and then *2 its result
	std::cout<<multiply_sum_fast<<std::endl;
	//sum_slow is never evaluated because it is never used.
}
