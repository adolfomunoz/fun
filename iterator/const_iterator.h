#ifndef _FUNCTIONAL_CONST_ITERATOR_H_
#define _FUNCTIONAL_CONST_ITERATOR_H_

namespace fun
{

template<typename I>
class ConstIteratorFacade
{
public:
	I& operator++()    { static_cast<I*>(this)->inc(); return static_cast<I&>(*this); }
	I  operator++(int) { I old(static_cast<I&>(*this)); static_cast<I*>(this)->inc(); return old; }
	bool operator==(const I& that) const { return static_cast<const I*>(this)->equals(that);  }
	bool operator!=(const I& that) const { return !static_cast<const I*>(this)->equals(that); }
};

};


#endif
