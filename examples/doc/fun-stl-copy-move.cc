#include "../../fun.h"
#include <list>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <chrono>

using fun::_;

std::list<int> create(unsigned int size) {
	std::list<int> sol;
	for (unsigned int i = 0;i<size;++i) {
		sol.push_back(2*(i%2) - 1);
	}
	return sol;
}

int main(int argc, char** argv) {
	unsigned int size = 10000;
	std::chrono::time_point<std::chrono::system_clock> start;
	int sol;
	std::chrono::duration<double> duration;
	double base_duration;
	
	for (int i = 0; i<argc-1; ++i)
	{
		if (strcmp("-size",argv[i])==0) size=atoi(argv[++i]);
	}
	
	
	{
	start = std::chrono::system_clock::now();
	std::list<int> l = create(size); //Move constructor
	sol = 2*l.front();
//	for (int i : l) sol+=2*i;	
	duration = std::chrono::system_clock::now() - start;
	base_duration = duration.count();
	std::cout<<"cpp     -> "
		<<std::setw(12)<<std::setprecision(6)<<sol<<" - "
		<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;
	}
	
	{
	start = std::chrono::system_clock::now();
	std::list<int> l = create(size); //Move constructor
	sol = fun::head(fun::map(_*2,l)); //fun::map copies l (copy constructor). SLOW
	duration = std::chrono::system_clock::now() - start;
	std::cout<<"copy    -> "
		<<std::setw(12)<<std::setprecision(6)<<sol<<" - "
		<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;
    }
	
	{
	start = std::chrono::system_clock::now();
	sol = fun::head(fun::map(_*2,create(size))); //fun::map calls move constructor.
	duration = std::chrono::system_clock::now() - start;
	std::cout<<"move    -> "
		<<std::setw(12)<<std::setprecision(6)<<sol<<" - "
		<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;
    }
}
