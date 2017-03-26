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
		sol+=r;	
	duration = std::chrono::system_clock::now() - start;
	double base_duration = duration.count();
	std::cout<<"take-cpp-> "
		<<std::setw(12)<<std::setprecision(6)<<sol<<" - "
		<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;

	start = std::chrono::system_clock::now();
	sol = fun::sum(fun::take(size,fun::randoms(0)));
	duration = std::chrono::system_clock::now() - start;
	std::cout<<"take    -> "
		<<std::setw(12)<<std::setprecision(6)<<sol<<" - "
		<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;

	start = std::chrono::system_clock::now();
	sol = fun::sum(fun::take_2(size,fun::randoms(0)));
	duration = std::chrono::system_clock::now() - start;
	std::cout<<"take_2  -> "
		<<std::setw(12)<<std::setprecision(6)<<sol<<" - "
		<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;
}
