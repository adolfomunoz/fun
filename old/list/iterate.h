#ifndef _FUNCTIONAL_ITERATE_H_
#define _FUNCTIONAL_ITERATE_H_

#include "core/forward-list.h"
#include "../function/function.h"
#include <type_traits>


namespace fun {

template<typename Function, typename ValueType>
class Iterated : public ForwardListImpl<Iterated<Function,ValueType>,ValueType>
{
	Function f; ValueType value;
	friend class const_iterator;
public:
	Iterated(const Function& _f, const ValueType& _value):
		f(_f), value(_value) { }
	Iterated(Function&& _f,      const ValueType& _value):
		f(std::forward<Function>(_f)), value(_value) { }
	Iterated(const Function& _f, ValueType&& _value):
		f(_f), value(std::forward<ValueType>(_value)) { }
	Iterated(Function&& _f,      ValueType&& _value):
		f(std::forward<Function>(_f)), value(std::forward<ValueType>(_value)) { }

	using value_type = ValueType; 

	class const_iterator_local 
	{
		friend class Iterated<Function, ValueType>;
		const Function& f; ValueType value;

	public:
		void inc() { value = f(value); }
		bool equals(const const_iterator_local& that) const { return false; }
		ValueType get() const { return value; } 		
		const_iterator_local(const Function& _f, const ValueType& _value) : 
			f(_f), value(_value) { } 
	};

	const_iterator_local begin_local() const { return const_iterator_local(f, value);  }
	const_iterator_local end_local()   const { return const_iterator_local(f, value); }
};

template<typename Function, typename ValueType>
auto iterate_(Function&& f, ValueType&& value)
{	return Iterated<typename std::remove_reference<Function>::type,
			typename std::remove_reference<ValueType>::type>(
				std::forward<Function>(f),std::forward<ValueType>(value));  }

/**************************************
 * fun::API                           *
 **************************************/
auto iterate = function<2>([] (auto&& p1, auto&& p2) { return iterate_(p1, p2); });


}; //namespace fun

#endif
