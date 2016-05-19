#include "../fun.h"
#include <string.h>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <list>
#include <cmath>

#include <utility>
#include <functional>

using fun::_;

auto sqr        = fun::function<1>([] (float r) -> float { return r*r; });


auto fun_volume = fun::function<3>([] (unsigned int dimensions, float radius, unsigned long nsamples) -> float
{
	return (std::pow(2.0f*radius, dimensions)/float(nsamples))*
		((fun::length & fun::filter(_<=1.0f) & fun::foldl1(fun::zipWith(_+_))) 
		      (fun::map(fun::map(sqr & (_-1) & ((2*radius)*_)) & fun::take(nsamples) & fun::randoms,fun::take(dimensions,fun::randomSeedsIO()))));
});

int main(int argc, char** argv)
{
	std::cout<<fun::map([] (unsigned int nd) { return fun_volume(nd, 1.0, 1000000); }, fun::range(1,6))<<std::endl;
}
