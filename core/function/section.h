#pragma once

#include "function.h"

namespace fun {

class Section {
public:
	template<typename O2>
	auto operator+(const O2& o2) const
	{	return function<generic::a, generic::b>([o2] (const auto& o1) { return o1+o2; }); 	}

	template<typename O1>
	friend auto operator+(const O1& o1, const Section o2) 
        {	return function<generic::a, generic::b>([o1] (const auto& o2) { return o1+o2; });    }	

	auto operator+(const Section& o2) const
	{	return function<generic::a, generic::b, generic::c>([] (const auto& o1, const auto& o2) { return o1+o2; }); 	}

	template<typename O2>
	auto operator-(const O2& o2) const
	{	return function<generic::a, generic::b>([o2] (const auto& o1) { return o1-o2; }); 	}

	template<typename O1>
	friend auto operator-(const O1& o1, const Section o2) 
        {	return function<generic::a, generic::b>([o1] (const auto& o2) { return o1-o2; });    }	

	auto operator-(const Section& o2) const
	{	return function<generic::a, generic::b, generic::c>([] (const auto& o1, const auto& o2) { return o1-o2; }); 	}

	template<typename O2>
	auto operator*(const O2& o2) const
	{	return function<generic::a, generic::b>([o2] (const auto& o1) { return o1*o2; }); 	}

	template<typename O1>
	friend auto operator*(const O1& o1, const Section o2) 
        {	return function<generic::a, generic::b>([o1] (const auto& o2) { return o1*o2; });    }	

	auto operator*(const Section& o2) const
	{	return function<generic::a, generic::b, generic::c>([] (const auto& o1, const auto& o2) { return o1*o2; }); 	}

	template<typename O2>
	auto operator/(const O2& o2) const
	{	return function<generic::a, generic::b>([o2] (const auto& o1) { return o1/o2; }); 	}

	template<typename O1>
	friend auto operator/(const O1& o1, const Section o2) 
        {	return function<generic::a, generic::b>([o1] (const auto& o2) { return o1/o2; });    }	

	auto operator/(const Section& o2) const
	{	return function<generic::a, generic::b, generic::c>([] (const auto& o1, const auto& o2) { return o1/o2; }); 	}

	template<typename O2>
	auto operator%(const O2& o2) const
	{	return function<generic::a, generic::b>([o2] (const auto& o1) { return o1%o2; }); 	}

	template<typename O1>
	friend auto operator%(const O1& o1, const Section o2) 
        {	return function<generic::a, generic::b>([o1] (const auto& o2) { return o1%o2; });    }	

	auto operator%(const Section& o2) const
	{	return function<generic::a, generic::b, generic::c>([] (const auto& o1, const auto& o2) { return o1%o2; }); 	}

	template<typename O2>
	auto operator==(const O2& o2) const
	{	return function<generic::a,bool>([o2] (const auto& o1) { return o1==o2; }); 	}

	template<typename O1>
	friend auto operator==(const O1& o1, const Section o2) 
        {	return function<generic::a,bool>([o1] (const auto& o2) { return o1==o2; });    }	

	auto operator==(const Section& o2) const
	{	return function<generic::a, generic::a, bool>([] (const auto& o1, const auto& o2) { return o1==o2; }); 	}

	template<typename O2>
	auto operator!=(const O2& o2) const
	{	return function<generic::a, bool>([o2] (const auto& o1) { return o1!=o2; }); 	}

	template<typename O1>
	friend auto operator!=(const O1& o1, const Section o2) 
        {	return function<generic::a, bool>([o1] (const auto& o2) { return o1!=o2; });    }	

	auto operator!=(const Section& o2) const
	{	return function<generic::a, generic::a, bool>([] (const auto& o1, const auto& o2) { return o1!=o2; }); 	}

	template<typename O2>
	auto operator>=(const O2& o2) const
	{	return function<generic::a, bool>([o2] (const auto& o1) { return o1>=o2; }); 	}

	template<typename O1>
	friend auto operator>=(const O1& o1, const Section o2) 
        {	return function<generic::a, bool>([o1] (const auto& o2) { return o1>=o2; });    }	

	auto operator>=(const Section& o2) const
	{	return function<generic::a, generic::a, bool>([] (const auto& o1, const auto& o2) { return o1>=o2; }); 	}

	template<typename O2>
	auto operator<=(const O2& o2) const
	{	return function<generic::a, bool>([o2] (const auto& o1) { return o1<=o2; }); 	}

	template<typename O1>
	friend auto operator<=(const O1& o1, const Section o2) 
        {	return function<generic::a, bool>([o1] (const auto& o2) { return o1<=o2; });    }	

	auto operator<=(const Section& o2) const
	{	return function<generic::a, generic::a, bool>([] (const auto& o1, const auto& o2) { return o1<=o2; }); 	}

	template<typename O2>
	auto operator>(const O2& o2) const
	{	return function<generic::a, bool>([o2] (const auto& o1) { return o1>o2; }); 	}

	template<typename O1>
	friend auto operator>(const O1& o1, const Section o2) 
        {	return function<generic::a, bool>([o1] (const auto& o2) { return o1>o2; });    }	

	auto operator>(const Section& o2) const
	{	return function<generic::a, generic::a, bool>([] (const auto& o1, const auto& o2) { return o1>o2; }); 	}

	template<typename O2>
	auto operator<(const O2& o2) const
	{	return function<generic::a, bool>([o2] (const auto& o1) { return o1<o2; }); 	}


	template<typename O1>
	friend auto operator<(const O1& o1, const Section o2) 
        {	return function<generic::a, bool>([o1] (const auto& o2) { return o1<o2; });    }	

	auto operator<(const Section& o2) const
	{	return function<generic::a, generic::a, bool>([] (const auto& o1, const auto& o2) { return o1<o2; }); 	}

	template<typename O2>
	auto operator&&(const O2& o2) const
	{	return function<bool,bool>([o2] (const auto& o1) { return o1&&o2; }); 	}

	template<typename O1>
	friend auto operator&&(const O1& o1, const Section o2) 
        {	return function<bool,bool>([o1] (const auto& o2) { return o1&&o2; });    }	

	auto operator&&(const Section& o2) const
	{	return function<bool,bool,bool>([] (const auto& o1, const auto& o2) { return o1&&o2; }); 	}

	template<typename O2>
	auto operator&(const O2& o2) const
	{	return function<generic::a, generic::a>([o2] (const auto& o1) { return o1&o2; }); 	}

	template<typename O1>
	friend auto operator&(const O1& o1, const Section o2) 
        {	return function<generic::a, generic::a>([o1] (const auto& o2) { return o1&o2; });    }	

	auto operator&(const Section& o2) const
	{	return function<generic::a, generic::a, generic::a>([] (const auto& o1, const auto& o2) { return o1&o2; }); 	}

	template<typename O2>
	auto operator||(const O2& o2) const
	{	return function<bool,bool>([o2] (const auto& o1) { return o1||o2; }); 	}

	template<typename O1>
	friend auto operator||(const O1& o1, const Section o2) 
        {	return function<bool,bool>([o1] (const auto& o2) { return o1||o2; });    }	

	auto operator||(const Section& o2) const
	{	return function<bool,bool,bool>([] (const auto& o1, const auto& o2) { return o1||o2; }); 	}

	template<typename O2>
	auto operator|(const O2& o2) const
	{	return function<generic::a, generic::a>([o2] (const auto& o1) { return o1|o2; }); 	}

	template<typename O1>
	friend auto operator|(const O1& o1, const Section o2) 
        {	return function<generic::a, generic::a>([o1] (const auto& o2) { return o1|o2; });    }	

	auto operator|(const Section& o2) const
	{	return function<generic::a, generic::a, generic::a>([] (const auto& o1, const auto& o2) { return o1|o2; }); 	}

	auto operator!() const
	{	return function<bool,bool>([] (const auto& o1) { return !o1; }); 			}

	auto operator*() const
	{	return function<generic::a, generic::b>([] (const auto& o1) { return *o1; }); 			}



};


/**************************************
 * fun::API                           *
 **************************************/
Section _;

}; //namespace fun

