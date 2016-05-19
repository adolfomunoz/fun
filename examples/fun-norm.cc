#include "../fun.h"
#include <string.h>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <list>
#include <cmath>

#include <utility>
#include <functional>


template<typename L>
auto norm_fe(const L& l, double e)
{	
	auto pow = [] (double o1, double o2) { return std::pow(o1,o2); };
	return pow(fun::sum(fun::map(fun::curry(fun::flip(pow),e),l)),1.0/e);     
}

template<typename L>
double norm_cp(const L& l, double e)
{	
	double sum = 0.0;
	for (auto i : l) sum += std::pow(i, e);

	return std::pow(sum, 1.0/e);
}


int main(int argc, char** argv)
{
	std::list<double> l;
	unsigned long size = 100000000;
	double  e = 4.0;

	for (int i = 0;i<argc - 1;++i) {
		if (strcmp("-size",argv[i])==0) size=atol(argv[++i]);
		else if (strcmp("-e",argv[i])==0) e=atof(argv[++i]);
	}

	for (unsigned int i = 0; i<size; ++i)
		l.push_back(1.0); 

	std::cerr<<"E = "<<e<<" - Size = "<<size<<" - Solution = "<<std::pow(size, 1.0/e)<<std::endl;

	std::chrono::time_point<std::chrono::system_clock> start;
	double sol;
	std::chrono::duration<double> duration;

	start = std::chrono::system_clock::now();
	sol = norm_cp(l, e);
	duration = std::chrono::system_clock::now() - start;
	double base_duration = duration.count();
	std::cout<<"Cpp standard          -> "<<sol<<" - "<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;

	start = std::chrono::system_clock::now();
	sol = norm_fe(l, e);
	duration = std::chrono::system_clock::now() - start;
	std::cout<<"As fun definition     -> "<<sol<<" - "<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl; 

	auto pow = fun::function<2>([] (double o1, double o2) { return std::pow(o1,o2); });
	auto norm_fi = fun::flip(pow)(1.0/e) & fun::sum & fun::map(fun::flip(pow)(e));
	start = std::chrono::system_clock::now();
	sol = norm_fi(l);
	duration = std::chrono::system_clock::now() - start;
	std::cout<<"As fun awesome        -> "<<sol<<" - "<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl; 

}
