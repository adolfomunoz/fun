#include "../../fun.h"
#include <string.h>

using fun::_;

auto map_explore  = fun::function<2>([] (auto&& f, auto&& l) {
	return fun::explore([f] (auto& i) { return f(*(i++)); },l);
});


int main(int argc, char** argv) {
	unsigned int size = 10000;
	for (int i = 0; i<argc-1; ++i)
	{
		if (strcmp("-size",argv[i])==0) size=atoi(argv[++i]);
	}
	std::cout<<fun::sum(map_explore(_*2.0,fun::take(size,fun::randoms(0))))<<std::endl;
}
