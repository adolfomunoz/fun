#ifndef _FUNCTIONAL_LIST_CONSTRUCTORS_H_
#define _FUNCTIONAL_LIST_CONSTRUCTORS_H_

#include <array>

namespace fun {

/**
 * We construct lists using a std::array. It is static and small. We might want to define our own
 * array-like list for this matter, though, that has all the operators that ForwardLists have
 * (or maybe more, as it has random access).
 **/

template<typename T>
std::array<T,1> l(const T& t1) { return std::array<T,1>{{t1}}; }

template<typename T>
std::array<T,2> l(const T& t1, const T& t2) { return std::array<T,2>{{t1,t2}}; }

template<typename T>
std::array<T,3> l(const T& t1, const T& t2, const T& t3) { return std::array<T,3>{{t1,t2,t3}}; }

template<typename T>
std::array<T,4> l(const T& t1, const T& t2, const T& t3, const T& t4) { return std::array<T,4>{{t1,t2,t3,t4}}; }

};

#endif
