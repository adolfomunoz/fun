#pragma once

#include <type_traits>
#include <cmath>

namespace fun {

struct Floating {
	template<typename T>
	struct check {
		static constexpr bool value = std::is_floating_point_v<T>;
    };
};

auto exp = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::exp(a); });
auto log = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::log(a); });
auto sqrt = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::sqrt(a); });
auto pow = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::pow(a); }); //Can't do '**'
auto sin = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::sin(a); }); 
auto cos = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::cos(a); }); 
auto tan = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::tan(a); }); 
auto asin = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::asin(a); }); 
auto acos = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::acos(a); }); 
auto atan = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::acos(a); }); 
auto sinh = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::sinh(a); }); 
auto cosh = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::cosh(a); }); 
auto tanh = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::tanh(a); });
auto asinh = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::asinh(a); }); 
auto acosh = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::acosh(a); }); 
auto atanh = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& a) { return std::atanh(a); }); 	
auto logBase = function<classes<Floating,generic::a>,generic::a, generic::a>(
	[] (const auto& b, const auto& x) { return std::log(x)/std::log(b); });
auto pi = function<classes<Floating,generic::a>,generic::a>(
	[] () { return M_PI; });
}
