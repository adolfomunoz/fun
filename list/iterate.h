#ifndef _FUNCTIONAL_ITERATE_H_
#define _FUNCTIONAL_ITERATE_H_

#include "../iterator/const_iterator.h"
#include <type_traits>


namespace fun {

template<typename Function, typename ValueType>
class Iterated 
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

	class const_iterator : public ConstIteratorFacade<const_iterator>
	{
		friend class Iterated<Function, ValueType>;
		const Function& f; ValueType value;

		const_iterator(const Function& _f, const ValueType& _value) : 
			f(_f), value(_value) { } 
	public:
		void inc() { value = f(value); }
		bool equals(const const_iterator& that) const { return false; }
		const ValueType& operator*() const { return value; } 		
	};

	const_iterator begin() const { return const_iterator(f, value);  }
	const_iterator end()   const { return const_iterator(f, value); }
};

template<typename Function, typename ValueType>
auto iterate_(Function&& f, ValueType&& value)
{	return Iterated<typename std::remove_reference<Function>::type,
			typename std::remove_reference<ValueType>::type>(
				std::forward<Function>(f),std::forward<ValueType>(value));  }

/**************************************
 * fun::API                           *
 **************************************/
auto iterate = [] (auto&& p1, auto&& p2) { return iterate_(p1, p2); };


}; //namespace fun

#endif
