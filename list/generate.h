#ifndef _FUNCTIONAL_GENERATE_H_
#define _FUNCTIONAL_GENERATE_H_

#include "../iterator/const_iterator.h"
#include <type_traits>


namespace fun {

template<typename Generator>
class Generated
{
	Generator generator;
	friend class const_iterator;
public:
	Generated(const Generator& _generator):
		generator(_generator) { }
	Generated(Generator&& _generator):
		generator(std::forward<Generator>(_generator)) { }

	using value_type = decltype(generator());

	class const_iterator : public ConstIteratorFacade<const_iterator>
	{
		friend class Generated<Generator>;
		const Generated<Generator>* g;
	        typename Generated<Generator>::value_type value;	

		const_iterator(const Generated<Generator>* _g = 0) : g(_g) 
		{ if (_g) value = _g->generator(); }
	public:
		void inc() { value = g->generator(); }
		bool equals(const const_iterator& that) const { return this->g == that.g; }
		typename Generated<Generator>::value_type operator*() const { return value; } 		
	};

	const_iterator begin() const { return const_iterator(this);  }
	const_iterator end()   const { return const_iterator(); }
};

template<typename Generator>
auto generate_(Generator&& generator)
{	return Generated<typename std::remove_reference<Generator>::type>(
			std::forward<Generator>(generator));  }

/**************************************
 * fun::API                           *
 **************************************/
auto generate = [] (auto&& p1) { return generate_(p1); };


}; //namespace fun

#endif
