#ifndef _FUNCTIONAL_LIST_OF_SELF_H_
#define _FUNCTIONAL_LIST_OF_SELF_H_

//#include "../iterator/const_iterator.h"

namespace fun {

/**
 * \brief Any class that inherits from this becomes also a list in which it is the only element
 */
/*
template<typename Self>
class ListOfSelf
{
	friend class const_iterator;
public:
	class const_iterator : public ConstIteratorFacade<const_iterator>
	{
		friend class ListOfSelf<Self>;
		const Self* s;
		bool done;

		const_iterator(const Self* _s) : 
			s(_s), done(false) { }

	public:
		//Temporary here, make it private afterwards
		const_iterator() : done(true) { }

		void inc() { done = true; } 
		bool equals(const const_iterator& that) const { return this->done == that.done; }
		const Self& operator*() const { return (*s); } 		
	};

	const_iterator begin() const { return const_iterator(static_cast<const Self*>(this));  }
	const_iterator end()   const { return const_iterator(); }

	using value_type = Self;
};
*/

}; //namespace fun

#endif
