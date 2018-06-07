#include <fun.h>
#include <iostream>

template<typename T, typename Repl>
void test_replacements() {
	std::cout<<"Type        : "<<fun::typeinfo<T>::name()<<std::endl;
	std::cout<<"Replacement : "<<fun::typeinfo<Repl>::name()<<std::endl;
	std::cout<<"New type    : "<<fun::typeinfo<fun::apply_replacements_t<Repl,T>>::name()<<std::endl<<std::endl;;
};

int main(int argc, char** argv) {
	using replacement1 = fun::generic_replacement_t<0, double, fun::generic_replacement_t<2,int>>;
	test_replacements<fun::type<fun::Tuple,fun::generic::a>,replacement1>();
	test_replacements<fun::type<fun::Tuple,fun::generic::b>,replacement1>();
	test_replacements<fun::type<fun::Tuple,fun::generic::c>,replacement1>();
	test_replacements<fun::type<fun::Tuple,fun::generic::a,int,fun::generic::c>,replacement1>();
	test_replacements<fun::type<fun::Tuple,fun::generic::a,int,fun::generic::a>,replacement1>();
}
