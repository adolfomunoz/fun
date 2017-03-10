#ifndef _FUNCTIONAL_SECTION_H_
#define _FUNCTIONAL_SECTION_H_

#include "function.h"

namespace fun {

class Section {
public:
	template<typename O2>
	auto operator+(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1+o2; }); 	}

	template<typename O1>
	friend auto operator+(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1+o2; });    }	

	auto operator+(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1+o2; }); 	}

	template<typename O2>
	auto operator-(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1-o2; }); 	}

	template<typename O1>
	friend auto operator-(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1-o2; });    }	

	auto operator-(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1-o2; }); 	}

	template<typename O2>
	auto operator*(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1*o2; }); 	}

	template<typename O1>
	friend auto operator*(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1*o2; });    }	

	auto operator*(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1*o2; }); 	}

	template<typename O2>
	auto operator/(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1/o2; }); 	}

	template<typename O1>
	friend auto operator/(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1/o2; });    }	

	auto operator/(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1/o2; }); 	}

	template<typename O2>
	auto operator%(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1%o2; }); 	}

	template<typename O1>
	friend auto operator%(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1%o2; });    }	

	auto operator%(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1%o2; }); 	}

	template<typename O2>
	auto operator==(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1==o2; }); 	}

	template<typename O1>
	friend auto operator==(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1==o2; });    }	

	auto operator==(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1==o2; }); 	}

	template<typename O2>
	auto operator!=(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1!=o2; }); 	}

	template<typename O1>
	friend auto operator!=(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1!=o2; });    }	

	auto operator!=(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1!=o2; }); 	}

	template<typename O2>
	auto operator>=(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1>=o2; }); 	}

	template<typename O1>
	friend auto operator>=(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1>=o2; });    }	

	auto operator>=(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1>=o2; }); 	}

	template<typename O2>
	auto operator<=(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1<=o2; }); 	}

	template<typename O1>
	friend auto operator<=(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1<=o2; });    }	

	auto operator<=(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1<=o2; }); 	}

	template<typename O2>
	auto operator>(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1>o2; }); 	}

	template<typename O1>
	friend auto operator>(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1>o2; });    }	

	auto operator>(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1>o2; }); 	}

	template<typename O2>
	auto operator<(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1<o2; }); 	}

	template<typename O1>
	friend auto operator<(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1<o2; });    }	

	auto operator<(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1<o2; }); 	}

	template<typename O2>
	auto operator&&(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1&&o2; }); 	}

	template<typename O1>
	friend auto operator&&(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1&&o2; });    }	

	auto operator&&(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1&&o2; }); 	}

	template<typename O2>
	auto operator&(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1&o2; }); 	}

	template<typename O1>
	friend auto operator&(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1&o2; });    }	

	auto operator&(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1&o2; }); 	}

	template<typename O2>
	auto operator||(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1||o2; }); 	}

	template<typename O1>
	friend auto operator||(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1||o2; });    }	

	auto operator||(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1||o2; }); 	}

	template<typename O2>
	auto operator|(const O2& o2) const
	{	return function<1>([o2] (const auto& o1) { return o1|o2; }); 	}

	template<typename O1>
	friend auto operator|(const O1& o1, const Section o2) 
        {	return function<1>([o1] (const auto& o2) { return o1|o2; });    }	

	auto operator|(const Section& o2) const
	{	return function<2>([] (const auto& o1, const auto& o2) { return o1|o2; }); 	}

	auto operator!() const
	{	return function<1>([] (const auto& o1) { return !o1; }); 			}

	auto operator*() const
	{	return function<1>([] (const auto& o1) { return *o1; }); 			}



};


/**************************************
 * fun::API                           *
 **************************************/
Section _;

}; //namespace fun

#endif
