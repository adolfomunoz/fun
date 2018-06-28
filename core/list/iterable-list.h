#pragma once

#include "iterable-list-impl.h"
#include "list-proxy.h"
#include <list>

namespace fun
{

template<typename T>
class IterableList {
	
	std::shared_ptr<IterableListPolymorphic<T>> base;
public:
	IterableList() { }
	
	IterableList(const IterableList<T>& l) :
		//base(l.base->clone())
		base(l.base) // As the list should not be modified nor deleted, we don't clone it, we just share the pointer.... 
	{ 
//                std::cerr<<"IterableList(const IterableList<L>&) "<<typeid(*base).name()<<std::endl;	
	}
	
	IterableList(IterableList<T>&& l) :
		base(std::move(l.base)) {
//	        std::cerr<<"IterableList(IterableList<L>&&) "<<typeid(*base).name()<<std::endl;	       
	}


	template<typename L>
	IterableList(const L& l) :
		base(std::make_shared<L>(l)) 
	{ static_assert(std::is_base_of<IterableListPolymorphic<T>, L>::value, 
        			"The list L must be a descendant of IterableListPolymorphic<T>"); 
//                std::cerr<<"IterableList(const L&) "<<typeid(*base).name()<<std::endl;	
	}

	template<typename L>
	IterableList(L&& l) :
		base(std::make_shared<L>(std::forward<L>(l))) 
	{ static_assert(std::is_base_of<IterableListPolymorphic<T>, L>::value, 
        			"The list L must be a descendant of IterableListPolymorphic<T>");
//                std::cerr<<"IterableList(L&&) "<<typeid(*base).name()<<std::endl;	
	}
	
	IterableList(const std::list<T>& l) :
		IterableList(list_proxy(l)) { }
	
	IterableList(std::list<T>&& l) :
		IterableList(list_proxy(std::forward<std::list<T>>(l))) { }
	
	template<typename L>
	IterableList<T>& operator=(const L& l) 
	{	base = std::make_shared<L>(l); 
		static_assert(std::is_base_of<IterableListPolymorphic<T>, L>::value, 
        			"The list L must be a descendant of IterableListPolymorphic<T>");
//                std::cerr<<"operator=(const L&) "<<typeid(*base).name()<<std::endl;	
		return (*this); }
	template<typename L>
	IterableList<T>& operator=(L&& l)
	{	base = std::make_shared<L>(std::forward<L>(l));  
		static_assert(std::is_base_of<IterableListPolymorphic<T>, L>::value, 
        			"The list L must be a descendant of IterableListPolymorphic<T>");
//                std::cerr<<"operator=(L&&) "<<typeid(*base).name()<<std::endl;	
		return (*this); }
		
	IterableList<T>& operator=(const IterableList<T>& l) 
	{	//base = l.base->clone(); 
	        base = l.base;	// As the list should not be modified nor deleted, we don't clone it, we just share the pointer.... 
//                std::cerr<<"operator=(const IterableList<L>&) "<<typeid(*base).name()<<std::endl;	
		return (*this);  }
		
	IterableList<T>& operator=(IterableList<T>&& l) 
	{	base = std::move(l.base);   
//                std::cerr<<"operator=(IterableList<L>&&) "<<typeid(*base).name()<<std::endl;	
		return (*this); }
		
	IterableList<T>& operator=(const std::list<T>& l) {
		return (*this) = list_proxy(l);
	}

	IterableList<T>& operator=(std::list<T>&& l) {
		return (*this) = list_proxy(std::forward<std::list<T>>(l));
	}


	using value_type = T;
	
	class const_iterator {
		std::shared_ptr<IterableListPolymorphic<T>> list;
		std::unique_ptr<typename IterableListPolymorphic<T>::ConstIteratorPolymorphic> base;
		friend class IterableList<T>;
	public:
		const_iterator(const std::shared_ptr<IterableListPolymorphic<T>>& l, std::unique_ptr<typename IterableListPolymorphic<T>::ConstIteratorPolymorphic>&& b) : list(l), base(std::forward<std::unique_ptr<typename IterableListPolymorphic<T>::ConstIteratorPolymorphic>>(b)) { }
		const_iterator(const const_iterator& that) : list(that.list), base(that.base->clone())   { }
		const_iterator(const_iterator&& that)      : list(std::move(that.list)), base(std::move(that.base)) { }
		const_iterator& operator++()    {  base->inc(); return (*this); }
		bool operator==(const const_iterator& that) const { return base->equals(*(that.base)); }
		bool operator!=(const const_iterator& that) const { return !(base->equals(*(that.base))); }
		T operator*() const { return base->get(); }

		const_iterator& operator=(const const_iterator& that) 
		{  list=that.list;  base = that.base->clone();   return (*this); } 
		const_iterator& operator=(const_iterator&& that)      
		{  list=std::move(that.list);  base = std::move(that.base); return (*this); } 

		const_iterator operator++(int) {
			const_iterator old = (*this);
			base->inc();
			return old;
		}

	};

	const_iterator begin()  const { return const_iterator(this->base, this->base->make_iterator_begin()); }
	const_iterator end()    const { return const_iterator(this->base, this->base->make_iterator_end());   }

	T front() const { return *(begin()); }

	std::string type_name() {
		std::stringstream sstr;
		sstr<<"IterableList<"<<typeid(T).name()<<"> - "<<typeid(*base).name();
		return sstr.str();
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const IterableList<T>& l) {
	os<<"[";
	bool first = true;
	for (auto e : l) {
		if (first) first = false;
		else os<<",";
		os<<e<<std::flush;
	}
	os<<"]";
	return os;
};





};

