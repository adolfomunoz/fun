#include "../../fun.h"
#include <iostream>

using fun::_;

int main(int argc, char** argv)
{
	//Example 1
	//We uncurry the function (with a tuple).	
	auto ut_pow = fun::uncurry(fun::pow);
	//Now ut_pow expects a tuple with the two parameters for fun::pow
	std::cout<<ut_pow(std::make_tuple(2,4))<<std::endl;
	//Outputs 16
	
	//Example 2
	//We uncurry the function (with a list, all the parameters must be the same).	
	auto ul_pow = fun::uncurry_list(fun::pow);
	//Now ul_pow expects a list with the two parameters for fun::pow
	std::cout<<ul_pow(fun::l(2,4))<<std::endl;
	//Outputs 16

	//Example 3
	//We uncurry the function (with an iterator over a list, all the parameters must be the same).	
	auto ui_pow = fun::uncurry_iterator(fun::pow);
	//Now ul_pow expects an iterator over a list
	auto params = fun::l(2,4,3,3);
	auto iter   = params.begin();
	//Warning: side effect (iter is modified)
	std::cout<<ui_pow(iter)<<std::endl;
	//Outputs 16
	//Warning: iter has advanced as required (two steps). Again, side effect (iter is modified)
	std::cout<<ui_pow(iter)<<std::endl;
	//Outputs 27

	//Actually, this is what explore is for: it calls multiple times a function that takes an iterator
	//until the iterator reaches the end (warning: it might explode if there are even number of 
	//elements on the list.
	std::cout<<fun::explore(ui_pow, params)<<std::endl;
	//Outputs [16, 27], a list with two elements.

}
