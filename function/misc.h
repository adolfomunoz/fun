#ifndef _FUNCTIONAL_MISC_H_
#define _FUNCTIONAL_MISC_H_

#include "function.h"
#include <cmath>
#include "section.h"

namespace fun {

/**************************************
 * fun::API                           *
 **************************************/
auto abs  = fun::function<1>([] (const auto& f) { return std::abs(f); });
auto exp  = fun::function<1>([] (const auto& f) { return std::exp(f); });
auto log  = fun::function<1>([] (const auto& f) { return std::log(f); });
auto sqrt = fun::function<1>([] (const auto& f) { return std::sqrt(f); });
auto sin  = fun::function<1>([] (const auto& f) { return std::sin(f); });
auto cos  = fun::function<1>([] (const auto& f) { return std::cos(f); });
auto tan  = fun::function<1>([] (const auto& f) { return std::tan(f); });
auto asin  = fun::function<1>([] (const auto& f) { return std::asin(f); });
auto acos  = fun::function<1>([] (const auto& f) { return std::acos(f); });
auto atan  = fun::function<1>([] (const auto& f) { return std::atan(f); });
auto negate = (-1*_);
auto signum = fun::function<1>([] (auto f) { return decltype(f)((f<0)?-1:((f>0)?1:0)); });
auto pow   = fun::function<2>([] (const auto& b, const auto& e) { return std::pow(b,e); });
auto fst   = fun::function<1>([] (const auto& pair) { return std::get<0>(pair); });
auto snd   = fun::function<1>([] (const auto& pair) { return std::get<1>(pair); });
auto constant = fun::function<2>([] (const auto& c, const auto& dummy) { return c; });
auto max   = fun::function<2>([] (const auto& a, const auto& b) { return (a>b)?a:b; });
auto min   = fun::function<2>([] (const auto& a, const auto& b) { return (a<b)?a:b; });
auto isfinite = fun::function<1>([] (const auto& a) { return std::isfinite(a); });
auto isnan    = fun::function<1>([] (const auto& a) { return std::isnan(a); });
auto isinf    = fun::function<1>([] (const auto& a) { return std::isinf(a); });
auto dereference_and_advance = fun::function<1>([] (auto& i) { return *(i++); });

}; //namespace fun

#endif
