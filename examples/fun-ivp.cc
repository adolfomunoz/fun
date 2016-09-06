#include "../fun.h"
#include <iostream>
#include <iomanip>
#include <functional>


/**
 * step -> step size - real number
 * f    -> IVP Function, with the form y'(y) = f(t, y(t))
 * ty   -> tuple<real, ytype> where ytype is whatever y(t) returns
 * returns -> tuple<real, ytype> after a single step has been advanced
 **/
auto euler  = fun::function<3>([] (const auto& step, const auto& f, const auto& ty)
{	return std::make_tuple(fun::fst(ty)+step,fun::snd(ty)+step*f(fun::fst(ty),fun::snd(ty)));	});

/**
 * step -> step size - real number
 * f    -> IVP Function, with the form y'(y) = f(t, y(t))
 * ty   -> tuple<real, ytype> where ytype is whatever y(t) returns
 * returns -> tuple<real, ytype> after a single step has been advanced
 **/
auto rk2  = fun::function<3>([] (const auto& step, const auto& f, const auto& ty)
{ 
	auto k1 = step*f(fun::fst(ty),fun::snd(ty));
	auto k2 = step*f(fun::fst(ty)+0.5*step, fun::snd(ty)+0.5*k1);
	return std::make_tuple(fun::fst(ty)+step,fun::snd(ty)+k2);	
});

/**
 * step -> step size - real number
 * f    -> IVP Function, with the form y'(y) = f(t, y(t))
 * ty   -> tuple<real, ytype> where ytype is whatever y(t) returns
 * returns -> tuple<real, ytype> after a single step has been advanced
 **/
auto rk4  = fun::function<3>([] (const auto& step, const auto& f, const auto& ty)
{  	
	auto k1 = step*f(fun::fst(ty),fun::snd(ty));
	auto k2 = step*f(fun::fst(ty)+0.5*step, fun::snd(ty)+0.5*k1);
	auto k3 = step*f(fun::fst(ty)+0.5*step, fun::snd(ty)+0.5*k2);
	auto k4 = step*f(fun::fst(ty)+step, fun::snd(ty)+k3);
	return std::make_tuple(fun::fst(ty)+step,fun::snd(ty)+(1.0/6.0)*k1 + (1.0/3.0)*k2 + (1.0/3.0)*k3 + (1.0/6.0)*k4);
});


/**
 * method -> The stepper method to apply
 * n      -> integral - Number of steps to take
 * f    -> IVP Function, with the form y'(y) = f(t, y(t))
 * distance -> real - The distance to traverse in such number of steps
 **/
auto solver_steps = fun::function<4>([] (const auto& method, const auto& n, const auto& f, const auto& distance)
{	return fun::take(n+1) * fun::iterate(method(distance/n, f));	});

using fun::_;

int main(int argc, char** argv)
{
	//Solve the equation y' = y, starting at (t,y) = (0,1). This has the solution y = e^t. 
	
	//We want to compute y(1) (which equals e) using 10 steps
	auto solve_euler = solver_steps(euler,20);
	auto solve_rk2   = solver_steps(rk2,10);
	auto solve_rk4   = solver_steps(rk4,5);
	
	std::cout<<"euler -> "<<fun::show(fun::map(fun::snd, solve_euler([] (double t, double y) { return y; }, 1.0, std::make_tuple(0.0,1.0))))<<std::endl;
	std::cout<<"rk2   -> "<<fun::show(fun::map(fun::snd, solve_rk2([] (double t, double y) { return y; }, 1.0, std::make_tuple(0.0,1.0))))<<std::endl;
	std::cout<<"rk4   -> "<<fun::show(fun::map(fun::snd, solve_rk4([] (double t, double y) { return y; }, 1.0, std::make_tuple(0.0,1.0))))<<std::endl;

}
