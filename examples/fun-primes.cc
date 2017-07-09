#include "../fun.h"
#include <iostream>
#include <iomanip>
#include <functional>

using fun::_;

int main(int argc, char** argv)
{
	auto primes = fun::filter(
			[] (unsigned long n) { 
				return !fun::any((_==0) * (n % _), fun::range(2,1+int(sqrt(n)))); 
			},
			fun::range(1));

	for (auto number : fun::take(100, primes)) std::cout<<std::setw(7)<<number<<" ";
	std::cout<<std::endl<<std::endl;

	for (auto number : fun::takeWhile(fun::curry(std::greater<long>(),1000), primes)) 
		std::cout<<std::setw(7)<<number<<" ";
	std::cout<<std::endl;
}
