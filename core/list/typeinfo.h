#pragma once

#include "type.h"

namespace fun {

template<typename T> 
struct typeinfo<std::list<T>> {
public:
	static std::string name() { return std::string("[")+typeinfo<T>::name()+"]"; }
};

template<typename T> 
struct typeinfo<std::vector<T>> {
public:
	static std::string name() { return std::string("[")+typeinfo<T>::name()+"]"; }
};

template<typename T, std::size_t N> 
struct typeinfo<std::array<T,N>> {
public:
	static std::string name() { return std::string("[")+typeinfo<T>::name()+"]"; }
};

template<typename L, typename T> 
struct typeinfo<IterableListImpl<L,T>> {
public:
	static std::string name() { return std::string("[")+typeinfo<T>::name()+"]"; }
};

template<typename T> 
struct typeinfo<IterableList<T>> {
public:
	static std::string name() { return std::string("[")+typeinfo<T>::name()+"]"; }
};





}
