#pragma once

#include "../core/function/function.h"
#include "../core/function/type.h"

namespace fun {

auto id       = function<generic::a,generic::a>([] (const auto& i) { return i; });

auto constant = function<generic::a,generic::b,generic::a>([] (const auto& c, const auto& dummy) { return c; });

auto asTypeOf = function<generic::a,generic::a,generic::a>([] (const auto& c, const auto& dummy) { return c; });

auto flip = function<type<Function,generic::a,generic::b,generic::c>,generic::b,generic::a,generic::c>(
	[] (const auto& f, const auto& x, const auto& y) { return f(y,x); }
);

auto until = function<type<Function, generic::a, bool>, type<Function, generic::a, generic::a>, generic::a, generic::a>(
	[] (const auto& pred, const auto& f, const auto& x) { auto y = x; while(!pred(y)) y=f(y); return y; });


}
