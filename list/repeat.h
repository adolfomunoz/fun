#ifndef _FUNCTIONAL_REPEAT_H_
#define _FUNCTIONAL_REPEAT_H_

#include "../iterator/const_iterator.h"
#include <type_traits>


namespace fun {

template<typename ValueType>
class Repeated 
{
	ValueType value;
	friend class const_iterator;
public:
	Repeated(const ValueType& _value):
		value(_value) { }
	Repeated(ValueType&& _value):
		value(std::forward<ValueType>(_value)) { }

	using value_type = ValueType; 

	class const_iterator : public ConstIteratorFacade<const_iterator>
	{
		friend class Repeated<ValueType>;
		const ValueType& value;

		const_iterator(const ValueType& _value) : 
			value(_value) { } 
	public:
		void inc() { }
		bool equals(const const_iterator& that) const { return false; }
		const ValueType& operator*() const { return value; } 		
	};

	const_iterator begin() const { return const_iterator(value);  }
	const_iterator end()   const { return const_iterator(value); }
};

template<typename ValueType>
auto repeat_(ValueType&& value)
{	return Repeated<typename std::remove_reference<ValueType>::type>(
				std::forward<ValueType>(value));  }

/**************************************
 * fun::API                           *
 **************************************/
auto repeat = [] (auto&& p1) { return repeat_(p1); };


}; //namespace fun

#endif
