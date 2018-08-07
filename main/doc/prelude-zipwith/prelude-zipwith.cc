#include <tuple>
#include <iostream>
#include <fun.h>
#include <array>

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T,N>& v) {
	os<<"[";
	auto i = v.begin();
	while (i!=v.end()) {
		os<<(*i);
		if ((++i) != v.end()) os<<",";
	}
	os<<"]";
	return os;
}

#define SHOW(x) std::cout<<#x " = "<<std::flush<<x<<std::endl;
#define SHOWTYPE(x) std::cout<<"Type of " #x " = "<<typeinfo<decltype(x)>::name()<<std::endl;
using namespace fun;
int main(int argc, char** argv) {
	//map (a->b) -> [a] -> [b] 
	std::array<int,5> d1{{-1,2,-3,4,-5}};
	std::array<int,4> d2{{2,-1,3,-2}};
	SHOWTYPE(zipWith)
	SHOW(d1);
	SHOW(d2);
	SHOW(zipWith(_+_,d1,d2));
}
