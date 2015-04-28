#ifndef _FUNCTIONAL_RANGE_H_
#define _FUNCTIONAL_RANGE_H_

#include "../iterator/const_iterator.h"

namespace fun
{

template<typename Num>
class InfiniteRange
{
	Num start;
public:
	InfiniteRange(const Num& _start) :
		start(_start) { }

	class const_iterator : public ConstIteratorFacade<const_iterator>
	{
		friend class InfiniteRange<Num>;
		Num n; bool inf;
		const_iterator(const Num& _n) : n(_n), inf(false) { }
		const_iterator() : inf(true) { }
	public:
		void inc() { n++; }
		bool  equals(const const_iterator& that) const { return this->inf == that.inf; }
		Num operator*() const { return n; } 		
	};

	const_iterator begin() const { return const_iterator(start); }
	const_iterator end()   const { return const_iterator();      }

	using value_type = Num;
};

template<typename Num>
class Range
{
	Num start; Num finish;
public:
	Range(const Num& _start, const Num& _finish) :
		start(_start),finish(_finish) { }

	class const_iterator : public ConstIteratorFacade<const_iterator>
	{
		friend class Range<Num>;
		Num n; 
		const_iterator(const Num& _n) : n(_n) { }
	public:
		void inc() { n++; }
		bool equals(const const_iterator& that) const { return this->n >= that.n; }
		Num operator*() const { return n; } 
	};

	const_iterator begin() const { return const_iterator(start);  }
	const_iterator end()   const { return const_iterator(finish); }

	using value_type = Num;
};

template<typename Num>
class RangeStepped
{
	Num start; Num finish; Num step;
public:
	RangeStepped(const Num& _start, const Num& _finish, const Num& _step) :
		start(_start),finish(_finish),step(_step) { }

	class const_iterator : public ConstIteratorFacade<const_iterator>
	{
		friend class RangeStepped<Num>;
		Num n; const Num& step;
		const_iterator(const Num& _n, const Num& _step) : n(_n), step(_step) { }
	public:
		void inc() { n+=step; }
		bool equals(const const_iterator& that) const { return this->n >= that.n; }
		Num operator*() const { return n; } 
	};

	const_iterator begin() const { return const_iterator(start,  step); }
	const_iterator end()   const { return const_iterator(finish, step); }

	using value_type = Num;
};



template<typename Num>
InfiniteRange<Num> range_(const Num& start)
{	return InfiniteRange<Num>(start);  }

template<typename NumS, typename NumE>
Range<NumE> range_(const NumS& start, const NumE& end)
{	return Range<NumE>(NumE(start),end);  }

template<typename NumS, typename NumE, typename Num>
RangeStepped<Num> range_(const NumS& start, const NumE& end, const Num& step)
{	return RangeStepped<Num>(Num(start), Num(end), step);  }

/**************************************
 * fun::API                           *
 **************************************/
auto range = [] (auto... params) { return range_(params...); };



};

#endif //_FUNCTIONAL_SERIES_H_
