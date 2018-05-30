#include <iostream>
#include <fun.h>

int main(int argc, char** argv) {
	auto sum  = fun::function([] (int n1, int n2) { std::cout<<"sum("<<n1<<","<<n2<<")"<<std::endl; int s=0; for(int i=n1; i<=n2; ++i) s+=i; return s; });

	//sum_fast is not evaluated now
	auto sum_fast = sum(0,10); 
        //sum_slow is not evaluated now	
	auto sum_slow = sum(0,1000000);
	//sum_fast is evaluated now - prints sum(0,10) and then its result
	std::cout<<sum_fast<<std::endl;
	//sum_slow is never evaluated because it is never used.
}
