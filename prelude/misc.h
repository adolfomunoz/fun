#pragma once

#include "../core/function/function.h"

namespace fun {

auto id       = fun::function<generic::a,generic::a>([] (const auto& i) { return i; });
auto constant = fun::function<generic::a,generic::b,generic::a>([] (const auto& c, const auto& dummy) { return c; });
auto asTypeOf = fun::function<generic::a,generic::a,generic::a>([] (const auto& c, const auto& dummy) { return c; });

}
