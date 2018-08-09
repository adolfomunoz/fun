#include <fun.h>
#include <iostream>
#include <string>

template<typename... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<typename... Ts> overloaded(Ts...) -> overloaded<Ts...>;
using namespace fun;

template<typename T, typename Ts>
std::string show(const RecursiveList<T,Ts>& l) { 
	return std::visit(overloaded {
		[] (EmptyList e) { return std::string(""); },
		[] (const RecursiveListNode<T,Ts>& n) {
			return std::to_string(n.head())+" "+show(n.tail());
		}
	}, l);
}

int main(int argc, char** argv) {
	auto my_list = c(1,2,3);
	std::cout<<show(my_list.impl()())<<std::endl;
}
