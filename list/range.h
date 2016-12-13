#ifndef _FUNCTIONAL_RANGE_H_
#define _FUNCTIONAL_RANGE_H_

#include "../list-core/forward-list.h"

namespace fun
{

template<typename Num>
class InfiniteRange : public ForwardListImpl<InfiniteRange<Num>,Num>

{
	Num start;
public:
	InfiniteRange(const Num& _start) :
		start(_start) { }

	class const_iterator_local {
	private:
		Num n;
	public:
	        void inc() { ++n; }
	        Num get() const { return n; }
		bool equals(const const_iterator_local& that) const noexcept { return false; }
		const_iterator_local(const Num& _n) : n(_n) { }
	};

	const_iterator_local begin_local() const { return const_iterator_local(start); }
	const_iterator_local end_local()   const { return const_iterator_local(start); }

	using value_type = Num;
};

template<typename Num>
class Range : public ForwardListImpl<Range<Num>,Num>
{
	Num start; Num finish;
public:
	Range(const Num& _start, const Num& _finish) :
		start(_start),finish(_finish) { }

	class const_iterator_local {
		Num n; 
	public:
		const_iterator_local(const Num& _n) : n(_n) { }
		void inc() { ++n; }
		bool equals(const const_iterator_local& that) const { return this->n == that.n; }
		Num get() const { return n; } 
	};

	const_iterator_local begin_local() const { return const_iterator_local(start);  }
	const_iterator_local end_local()   const { Num f=finish; ++f; return const_iterator_local(f); }

	using value_type = Num;
};

template<typename Num>
class RangeStepped : public ForwardListImpl<RangeStepped<Num>,Num>
{
	Num start; Num finish; Num step;
public:
	RangeStepped(const Num& _start, const Num& _finish, const Num& _step) :
		start(_start),finish(_finish),step(_step) { }

	class const_iterator_local
	{
		Num n; Num f; Num step; bool reached;
	public:
		const_iterator_local(const Num& _n, const Num& _f, const Num& _step) : n(_n), f(_f), step(_step), reached(false) { }
		const_iterator_local() : reached(true) { }
		void inc() { if (n==f) reached=true; n+=step; if (n>=f) n=f; }
		bool equals(const const_iterator_local& that) const { return this->reached == that.reached; }
		Num get() const { return n; } 

	};

	const_iterator_local begin_local() const { return const_iterator_local(start,  finish, step); }
	const_iterator_local end_local()   const { return const_iterator_local(); }

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
