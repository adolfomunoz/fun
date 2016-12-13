#ifndef _FUNCTIONAL_REPEAT_H_
#define _FUNCTIONAL_REPEAT_H_

#include "../iterator/const_iterator.h"
#include <type_traits>


namespace fun {

template<typename ValueType>
class Repeated : public ForwardListImpl<Repeated<ValueType>,ValueType>

{
	ValueType value;
	friend class const_iterator;
public:
	Repeated(const ValueType& _value):
		value(_value) { }
	Repeated(ValueType&& _value):
		value(std::forward<ValueType>(_value)) { }

	using value_type = ValueType; 

	class const_iterator_local 
	{
		friend class Repeated<ValueType>;
		const ValueType& value;

	public:
		const_iterator_local(const ValueType& _value) : 
			value(_value) { } 
		void inc() { }
		bool equals(const const_iterator_local& that) const { return false; }
		ValueType get() const { return value; } 		
	};

	const_iterator_local begin_local() const { return const_iterator_local(value);  }
	const_iterator_local end_local()   const { return const_iterator_local(value); }
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
