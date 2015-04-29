#include "../fun.h"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <list>

#include <utility>
#include <functional>

template<typename L1, typename L2>
auto dot_fe(const L1& l1, const L2& l2)
{	return fun::sum(fun::zipWith(std::multiplies<double>(),l1,l2));	}

template<typename L1, typename L2>
double dot_cp(const L1& l1, const L2& l2)
{	
	typename L1::const_iterator i1;
	typename L2::const_iterator i2;
	double sol = 0.0;
	for (i1 = l1.begin(), i2 = l2.begin(); (i1 != l1.end()) && (i2 != l2.end()); ++i1, ++i2)
		sol += (*i1)*(*i2);

	return sol;
}


int main(int argc, char** argv)
{
	std::list<double> l1;
	std::list<double> l2;
	l1.push_back(1.0); l2.push_back(1.0);

	for (unsigned int i = 0; i<10000000; ++i)
	{
		l1.push_back(0.0); l1.push_back(1.0);
		l2.push_back(1.0); l2.push_back(0.0);
	}

	std::chrono::time_point<std::chrono::system_clock> start;
	double sol;
	std::chrono::duration<double> duration;

	start = std::chrono::system_clock::now();
	sol = dot_cp(l1, l2);
	duration = std::chrono::system_clock::now() - start;
	double base_duration = duration.count();
	std::cout<<"Cpp standard          -> "<<sol<<" - "<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;

	start = std::chrono::system_clock::now();
	sol = dot_fe(l1, l2);
	duration = std::chrono::system_clock::now() - start;
	std::cout<<"As fun definition     -> "<<sol<<" - "<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl; 

	auto dot_fi = fun::compose(fun::sum, fun::curry(fun::zipWith, std::multiplies<double>()));
  	start = std::chrono::system_clock::now();
	sol = dot_fi(l1, l2);
	duration = std::chrono::system_clock::now() - start;
	std::cout<<"As fun::compose       -> "<<sol<<" - "<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;
}
