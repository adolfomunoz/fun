#include "../../fun.h"
#include <string>
#include <iostream>

using fun::_;

int main(int argc, char** argv)
{
	//Example 1
	auto fun_atoi = fun::function<1>([] (const char* s) { return atoi(s); }); 
	std::cout<<(fun_atoi("3")+fun_atoi("2"))<<std::endl;
	//Outputs 5

	//Example 2
	auto clamp = fun::function<3>(
		[] (float low, float high, float value) {
	       		return ((value<low)?low:((value>high)?high:value));
	});
	std::cout<<clamp(-10.0f,10.0f,9.0f)<<std::endl;
	//Outputs 9 
	std::cout<<clamp(-10.0f,10.0f,11.0f)<<std::endl;
	//Outputs 10
	
	//We apply currying and function composition to create gamma curve from clamped values
	auto gamma = fun::flip(fun::pow)(1.0f/2.2f) * clamp(0.0f, 1.0f);
	std::cout<<gamma(0.9f)<<std::endl;
	//Outputs 0.953238
	std::cout<<gamma(1.2f)<<std::endl;
	//Outputs 1
	
		

}
