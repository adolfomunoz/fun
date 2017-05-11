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
		sol.push_back((i%5) - 2);
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
	sol = 0;
    for (int i : l) if ((i % 2) == 0) sol+=5*i;  
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
	sol = fun::sum(fun::map(_*5,fun::filter( (_==0)*(_%2),l))); 
	//fun::map and fun::filter copy (copy constructor). In this case, fun::filter copies. SLOW
	duration = std::chrono::system_clock::now() - start;
	std::cout<<"copy    -> "
		<<std::setw(12)<<std::setprecision(6)<<sol<<" - "
		<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;
    }
	
	{
	start = std::chrono::system_clock::now();
	sol = fun::sum(fun::map(_*5,fun::filter( (_==0)*(_%2),create(size))));
	//fun::map and fun::filter move (move constructor).
	duration = std::chrono::system_clock::now() - start;
	std::cout<<"move    -> "
		<<std::setw(12)<<std::setprecision(6)<<sol<<" - "
		<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;
    }


	{
	start = std::chrono::system_clock::now();
	fun::list<int> l = create(size); //Move constructor to polymorphic list
	sol = fun::sum(fun::map(_*5,fun::filter( (_==0)*(_%2),l)));
	//l is polymorphic (slower) but does not copy the whole list when used
	duration = std::chrono::system_clock::now() - start;
	std::cout<<"poly.   -> "
		<<std::setw(12)<<std::setprecision(6)<<sol<<" - "
		<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;
    }

	{
	start = std::chrono::system_clock::now();
	std::list<int> l = create(size);
	auto rl = fun::list_ref(l); 
	sol = fun::sum(fun::map(_*5,fun::filter( (_==0)*(_%2),rl)));
    //Reference to list, does not copy. Segfaults if l becomes out of scope or destroyed.
	duration = std::chrono::system_clock::now() - start;
	std::cout<<"ref     -> "
		<<std::setw(12)<<std::setprecision(6)<<sol<<" - "
		<<std::setw(10)<<std::setprecision(6)<<(1.e3*duration.count())<<"ms ("
		<<std::setw(7)<<std::setprecision(5)<<(100.0*duration.count()/base_duration)<<"%)"<<std::endl;
    }


}
