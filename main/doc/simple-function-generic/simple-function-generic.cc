#include <iostream>
#include <fun.h>
#include <string>

struct ToString {
	template<typename T>
    std::string operator()(const T& t) const { return std::to_string(t); }	
};

using namespace fun::generic;
int main(int argc, char** argv) {
	auto fun_tostring1 = fun::function<a, std::string>([] (const auto& f) 
		{ return std::to_string(f); });
	auto fun_tostring2 = fun::function<a, std::string>(ToString());
	ToString  cob;
	auto fun_tostring3 = fun::function<a, std::string>(cob);	

	std::cout<<fun_tostring1(42)<<" "<<fun_tostring1(3.14159276)<<" | "<<
		   fun_tostring2(42)<<" "<<fun_tostring2(3.14159276)<<" | "<<
		   fun_tostring3(42)<<" "<<fun_tostring3(3.14159276)<<std::endl;
}
