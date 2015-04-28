#include "../fun.h"
#include <iostream>
#include <iomanip>
#include <functional>

int main(int argc, char** argv)
{
	auto primes = fun::filter(
			[] (unsigned long n) { return !fun::any(
				fun::compose(fun::curry(std::equal_to<long>(),0), fun::curry(std::modulus<long>(),n)),
					fun::range(2,n-1)); },
			fun::range(1));

	for (auto number : fun::take(100, primes)) std::cout<<std::setw(7)<<number<<" ";
	std::cout<<std::endl<<std::endl;

	for (auto number : fun::takeWhile(fun::curry(std::greater<long>(),1000), primes)) 
		std::cout<<std::setw(7)<<number<<" ";
	std::cout<<std::endl;
}
