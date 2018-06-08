#include <fun.h>
#include <iostream>

template<typename T1, typename T2>
void test_match() {
	std::cout<<"Type to match : "<<fun::typeinfo<T1>::name()<<std::endl;
	std::cout<<"Matching type : "<<fun::typeinfo<T2>::name()<<std::endl;
	using match = fun::match<T1,T2>;
	if (!match::value) std::cout<<" --> Not a match "<<std::endl;
        else std::cout<<" --> Match width replacements: "<<fun::typeinfo<typename match::replacements>::name()<<std::endl;
	std::cout<<std::endl;
}


int main(int argc, char** argv) {
	test_match<int, int>();
	test_match<fun::generic::a, int>();
	test_match<fun::type<fun::Tuple, float, int>, fun::type<fun::Tuple,float, int>>();
	test_match<fun::type<fun::Tuple, float, fun::generic::b>, fun::type<fun::Tuple, float, int>>();
	test_match<fun::type<fun::Tuple, fun::generic::c, fun::generic::b>, fun::type<fun::Tuple, float, int>>();

	test_match<fun::type<fun::Tuple, fun::generic::a, fun::generic::b, int, fun::generic::a>, fun::type<fun::Tuple, float, double, int, float>>();
	test_match<fun::type<fun::Tuple, fun::generic::a, fun::generic::b, int, fun::generic::a>, fun::type<fun::Tuple, float, double, int, bool>>();
	test_match<fun::type<fun::Tuple, fun::generic::a, fun::generic::b, int, fun::generic::a>, fun::type<fun::Tuple, fun::generic::c, fun::generic::c, int, fun::generic::c>>();

	test_match<fun::type<fun::Tuple, fun::type<fun::Tuple, fun::generic::a, fun::generic::b>, fun::generic::a>, fun::type<fun::Tuple, int, double>>();
	test_match<fun::type<fun::Tuple, fun::type<fun::Tuple, fun::generic::a, fun::generic::b>, fun::generic::a>, fun::type<fun::Tuple, fun::type<fun::Tuple,double,int>, double>>();
	test_match<fun::type<fun::Tuple, fun::type<fun::Tuple, fun::generic::a, fun::generic::b>, fun::generic::a>, fun::type<fun::Tuple, fun::type<fun::Tuple,double,int>, bool>>();

}
