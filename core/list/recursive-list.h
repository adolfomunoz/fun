#pragma once

#include <variant>

namespace fun {

struct EmptyList {};

template<typename T, typename LazyRest>
class RecursiveListNode {
	T t;
	LazyRest lazy_rest;
public:
	RecursiveListNode(T&& t, LazyRest&& lazy_rest) :
		t(std::forward<T>(t)), lazy_rest(std::forward<LazyRest>(lazy_rest)) {}
	RecursiveListNode(const T& t, LazyRest&& lazy_rest) :
		t(t), lazy_rest(std::forward<LazyRest>(lazy_rest)) {}
	RecursiveListNode(T&& t, const LazyRest& lazy_rest) :
		t(std::forward<T>(t)), lazy_rest(lazy_rest) {}
	RecursiveListNode(const T& t, const LazyRest& lazy_rest) :
		t(t), lazy_rest(lazy_rest) {}
		
	const T& head() const { return t; }
	const LazyRest& tail() const  { return lazy_rest; }
};

template<typename T, typename LazyRest>
using RecursiveList = std::variant<EmptyList,RecursiveListNode<T, LazyRest>>;

}