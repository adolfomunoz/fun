#include <iostream>
#include <fun.h>

int main(int argc, char** argv) {
	auto atod = fun::function<const char*, double>(
		[] (const char* s) { return std::atof(s); });
	//We could not redefine $ so we use the % symbol for application. It's not the same but its precedence is rather good
	std::cout<<atod % "2.5"<<std::endl;
}
