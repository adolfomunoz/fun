#include "../fun.h"
#include <iostream>
#include <limits>

using fun::_;

int main(int argc, char** argv)
{
	fun::list<int> list1 = fun::map(2*_,fun::range(1,10));
	fun::list<int> list2 = fun::map(1+_,list1);
	fun::list<int> list3 = fun::zipWith(_+_,list1, list2);
	fun::list<int> list4 = fun::map(_%3,list2);
	fun::list<int> list5 = list1 + list2;

	std::cout<<fun::length(list1)<<" - "<<fun::show(list1)<<std::endl;
	std::cout<<fun::length(list2)<<" - "<<fun::show(list2)<<std::endl;
	std::cout<<fun::length(list3)<<" - "<<fun::show(list3)<<std::endl;
	std::cout<<fun::length(list4)<<" - "<<fun::show(list4)<<std::endl;
	std::cout<<fun::length(list5)<<" - "<<fun::show(list5)<<std::endl;

	list1 = fun::map(2*_,list1);
	std::cout<<fun::length(list1)<<" - "<<fun::show(list1)<<std::endl;
	list1 = fun::map(1+_,fun::map(2*_,list1));
	std::cout<<fun::length(list1)<<" - "<<fun::show(list1)<<std::endl;
}
