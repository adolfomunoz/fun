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

}; //namespace fun

#endif
