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

#define SHOW(x) std::cout<<#x " = "<<x<<std::endl;
#define SHOWTYPE(x) std::cout<<"Type of " #x " = "<<typeinfo<decltype(x)>::name()<<std::endl;
using namespace fun;
int main(int argc, char** argv) {
	//map (a->b) -> [a] -> [b] 
	std::array<int,5> d{{-1,2,-3,4,-5}};
	SHOWTYPE(map)
	SHOW(d);
	SHOW(map(fun::abs,d));
	SHOW(map(_*2,d));
	SHOW(map([] (int i) { if (i>0) return i+1; else return i-1; },d));
}
