#include "../../fun.h"
#include <string.h>

using fun::_;

int main(int argc, char** argv) {
	unsigned int size = 10000;
	for (int i = 0; i<argc-1; ++i)
	{
		if (strcmp("-size",argv[i])==0) size=atoi(argv[++i]);
	}
	double sum=0.0;
	for (auto r : fun::take(size,fun::randoms(0)))
		sum+=2.0*r;	
	std::cout<<sum<<std::endl;
}
