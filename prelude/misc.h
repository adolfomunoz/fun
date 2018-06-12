#pragma once

#include "../core/function/function.h"
#include "../core/function/type.h"
#include "../core/tuple/type.h"

namespace fun {

auto id       = function<generic::a,generic::a>([] (const auto& i) { return i; });

auto constant = function<generic::a,generic::b,generic::a>([] (const auto& c, const auto& dummy) { return c; });

auto asTypeOf = function<generic::a,generic::a,generic::a>([] (const auto& c, const auto& dummy) { return c; });

auto flip = function<type<Function,generic::a,generic::b,generic::c>,generic::b,generic::a,generic::c>(
	[] (const auto& f, const auto& x, const auto& y) { return f(y,x); }
);

auto curry = function<type<Function,type<Tuple, generic::a, generic::b>, generic::c>, generic::a, generic::b, generic::c>(
	[] (const auto& f, const auto& x, const auto& y) { return f(std::tuple(x,y)); }); 

auto uncurry = function<type<Function,generic::a, generic::b, generic::c>, type<Tuple, generic::a, generic::b>, generic::c>(
	[] (const auto& f, const auto& t) { return f(std::get<0>(t), std::get<1>(t)); });

auto fst = function<type<Tuple, generic::a, generic::b>, generic::a>([] (const auto& t) { return std::get<0>(t); });

auto snd = function<type<Tuple, generic::a, generic::b>, generic::b>([] (const auto& t) { return std::get<1>(t); });

}
