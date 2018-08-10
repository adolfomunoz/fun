#include <fun.h>
#include <iostream>
#include <string>

template<typename... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<typename... Ts> overloaded(Ts...) -> overloaded<Ts...>;
using namespace fun;
using namespace fun::generic;

namespace fun {
	template<typename Visitor, typename Visitable>
	auto visit(const Visitor& visitor, const Visitable& visitable) {
		return visitor(visitable);
	}
	
	template<typename Visitor, typename... VTypes>
	auto visit(const Visitor& visitor, const std::variant<VTypes...>& visitable) {
		return std::visit(visitor, visitable);
	}

	
	template<typename Visitor, typename Visitable,typename F, typename Classes>
	auto visit(const Visitor& visitor, const Function_<F,Classes,Visitable>& visitable) {
		return fun::visit(visitor, (visitable.impl())());
	}
};

auto show = fun::function_recursive<a,std::string>(
	[] (const auto& self, const auto& list) {
	return fun::visit(overloaded {
		[] (EmptyList e) { return std::string(""); },
		[&self] (const auto& n) {
			return std::to_string(n.head())+" "+std::string(self(n.tail()));
		}
	}, list);
});

int main(int argc, char** argv) {
	auto my_list = fun::c(1,2,3);
	std::cout<<show(my_list)<<std::endl;
}
