#include <iostream>
#include <fun.h>
#include <string>

using namespace fun::generic;
using fun::_;

int main(int argc, char** argv) {
	auto inc = _+1;
	std::cout<<"inc(3)="<<inc(3)<<std::endl;
	auto div4by = 4.0/_;
	std::cout<<"div4by(2.0)="<<div4by(2.0)<<std::endl;

	auto is_divisible_by_5 = (_==0)*(_%5);

	if (is_divisible_by_5(155)) std::cout<<"155 is divisible by 5"<<std::endl;
	else std::cout<<"155 is not divisible by 5"<<std::endl;
	if (is_divisible_by_5(42)) std::cout<<"42 is divisible by 5"<<std::endl;
	else std::cout<<"42 is not divisible by 5"<<std::endl;

}
