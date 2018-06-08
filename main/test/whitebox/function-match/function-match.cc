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

using namespace fun::generic;

int main(int argc, char** argv) {
	auto mod      = fun::function([] (int i, int j) { return i % j; });

	test_match<fun::type<fun::Function, int, int, int>, decltype(mod)>();
	test_match<fun::type<fun::Function, a, int, int>, decltype(mod)>();
	test_match<fun::type<fun::Function, a, b, int>, decltype(mod)>();
	test_match<fun::type<fun::Function, a, b, c>, decltype(mod)>();

	auto weird = fun::function<fun::type<fun::Function, fun::generic::a, fun::generic::b, fun::generic::c>, int>([] (const auto& f) { return 42; });

	test_match<fun::type<fun::Function,fun::type<fun::Function, a, b, c>,int>, decltype(weird)>();
	test_match<fun::type<fun::Function,fun::type<fun::Function, b, a, c>,int>, decltype(weird)>();
	test_match<fun::type<fun::Function,fun::type<fun::Function, b, a, c>,c>, decltype(weird)>();
	test_match<fun::type<fun::Function,fun::type<fun::Function, b, a, c>,a>, decltype(weird)>();
}
