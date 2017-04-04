#include "../../fun.h"
#include <string.h>
#include <iostream>
#include <iomanip>
#include <chrono>

using fun::_;

int main(int argc, char** argv) {
	unsigned int size = 10000;
	std::chrono::time_point<std::chrono::system_clock> start;
	float sol;
	std::chrono::duration<double> duration;

	for (int i = 0; i<argc-1; ++i)
	{
		if (strcmp("-size",argv[i])==0) size=atoi(argv[++i]);
	}
	
	start = std::chrono::system_clock::now();
	sol=0.0f;
	for (auto r : fun::take(size,fun::randoms(0)))
		if (r > 0.5f) sol+=r;
	
	duration = std::chrono::system_clock::now() - start;
	double base_duration = duration.count();
	std::cout<<"filter-cpp -> "
		<<std::setw(12)<<std::setprecision(6)<<sol<<" - "
		<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;

	start = std::chrono::system_clock::now();
	sol = fun::sum(fun::filter(_>0.5f,fun::take(size,fun::randoms(0))));
	duration = std::chrono::system_clock::now() - start;
	std::cout<<"filter     -> "
		<<std::setw(12)<<std::setprecision(6)<<sol<<" - "
		<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;
}
