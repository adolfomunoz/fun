#pragma once

#include "../core/function/function.h"
#include "../core/function/type.h"

namespace fun {

auto id       = fun::function<generic::a,generic::a>([] (const auto& i) { return i; });

auto constant = fun::function<generic::a,generic::b,generic::a>([] (const auto& c, const auto& dummy) { return c; });

auto asTypeOf = fun::function<generic::a,generic::a,generic::a>([] (const auto& c, const auto& dummy) { return c; });

auto flip = fun::function<fun::type<fun::Function,fun::generic::a,fun::generic::b,fun::generic::c>,fun::generic::b,fun::generic::a,fun::generic::c>(
	[] (const auto& f, const auto& x, const auto& y) { return f(y,x); }
);

}
