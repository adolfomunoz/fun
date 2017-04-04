#ifndef _FUNCTIONAL_FORWARD_LIST_H_
#define _FUNCTIONAL_FORWARD_LIST_H_

#include <memory>
#include <iostream>
#include <sstream>

namespace fun
{

/**
 * Polymorphic version, base class of all forward lists
 **/
template<typename T>
class ForwardListPolymorphic {

public:
	class ConstIteratorPolymorphic {
	public:
		virtual void inc() = 0;
		virtual T get() const = 0;
		virtual bool equals(const ConstIteratorPolymorphic& that) const = 0;
		virtual std::unique_ptr<ConstIteratorPolymorphic> clone() const = 0;
	};

	virtual std::unique_ptr<ConstIteratorPolymorphic> make_iterator_begin() const = 0; 	
	virtual std::unique_ptr<ConstIteratorPolymorphic> make_iterator_end() const = 0;
	virtual std::unique_ptr<ForwardListPolymorphic<T>> clone() const = 0;
};

template<typename T>
class ForwardList {
	std::shared_ptr<ForwardListPolymorphic<T>> base;
public:
	ForwardList() { }
	
	ForwardList(const ForwardList<T>& l) :
		base(l.base->clone()) 
	{ 
//                std::cerr<<"ForwardList(const ForwardList<L>&) "<<typeid(*base).name()<<std::endl;	
	}
	
	ForwardList(ForwardList<T>&& l) :
		base(std::move(l.base)) {
//	        std::cerr<<"ForwardList(ForwardList<L>&&) "<<typeid(*base).name()<<std::endl;	       
	}


	template<typename L>
	ForwardList(const L& l) :
		base(std::make_shared<L>(l)) 
	{ static_assert(std::is_base_of<ForwardListPolymorphic<T>, L>::value, 
        			"The list L must be a descendant of ForwardListPolymorphic<T>"); 
//                std::cerr<<"ForwardList(const L&) "<<typeid(*base).name()<<std::endl;	
	}

	template<typename L>
	ForwardList(L&& l) :
		base(std::make_shared<L>(l)) 
	{ static_assert(std::is_base_of<ForwardListPolymorphic<T>, L>::value, 
        			"The list L must be a descendant of ForwardListPolymorphic<T>");
//                std::cerr<<"ForwardList(L&&) "<<typeid(*base).name()<<std::endl;	
	}
	
	template<typename L>
	ForwardList<T>& operator=(const L& l) 
	{	base = std::make_shared<L>(l); 
		static_assert(std::is_base_of<ForwardListPolymorphic<T>, L>::value, 
        			"The list L must be a descendant of ForwardListPolymorphic<T>");
//                std::cerr<<"operator=(const L&) "<<typeid(*base).name()<<std::endl;	
		return (*this); }
	template<typename L>
	ForwardList<T>& operator=(L&& l)
	{	base = std::make_shared<L>(std::forward<L>(l));  
		static_assert(std::is_base_of<ForwardListPolymorphic<T>, L>::value, 
        			"The list L must be a descendant of ForwardListPolymorphic<T>");
//                std::cerr<<"operator=(L&&) "<<typeid(*base).name()<<std::endl;	
		return (*this); }
		
	ForwardList<T>& operator=(const ForwardList<T>& l) 
	{	base = l.base->clone();   
//                std::cerr<<"operator=(const ForwardList<L>&) "<<typeid(*base).name()<<std::endl;	
		return (*this);  }
		
	ForwardList<T>& operator=(ForwardList<T>&& l) 
	{	base = std::move(l.base);   
//                std::cerr<<"operator=(ForwardList<L>&&) "<<typeid(*base).name()<<std::endl;	
		return (*this); }



	using value_type = T;
	
	class const_iterator {
		std::shared_ptr<ForwardListPolymorphic<T>> list;
		std::unique_ptr<typename ForwardListPolymorphic<T>::ConstIteratorPolymorphic> base;
		friend class ForwardList<T>;
	public:
		const_iterator(const std::shared_ptr<ForwardListPolymorphic<T>>& l, std::unique_ptr<typename ForwardListPolymorphic<T>::ConstIteratorPolymorphic>&& b) : list(l), base(std::forward<std::unique_ptr<typename ForwardListPolymorphic<T>::ConstIteratorPolymorphic>>(b)) { }
		const_iterator(const const_iterator& that) : list(that.list), base(that.base->clone())   { }
		const_iterator(const_iterator&& that)      : list(std::move(that.list)), base(std::move(that.base)) { }
		const_iterator& operator++()    {  base->inc(); return (*this); }
		//can't do this one as polymorphic. Do we need it? const_iterator  operator++(int)
		bool operator==(const const_iterator& that) const { return base->equals(*that.base); }
		bool operator!=(const const_iterator& that) const { return !(base->equals(*that.base)); }
		T operator*() const { return base->get(); }

		const_iterator& operator=(const const_iterator& that) 
		{  list=that.list;  base = that.base->clone();   return (*this); } 
		const_iterator& operator=(const_iterator&& that)      
		{  list=std::move(that.list);  base = std::move(that.base); return (*this); } 
	};

	const_iterator begin()  const { return const_iterator(this->base, this->base->make_iterator_begin()); }
	const_iterator end()    const { return const_iterator(this->base, this->base->make_iterator_end());   }

	T front() const { return *(begin()); }

	std::string type_name() {
		std::stringstream sstr;
		sstr<<"ForwardList<"<<typeid(T).name()<<"> - "<<typeid(*base).name();
		return sstr.str();
	}
};

/**
 * Implementation version with CRPT, not polymorphic
 **/
template<typename L, typename T>
class ForwardListImpl : public ForwardListPolymorphic<T> {
	//Must redefine:
	//    class const_iterator_local {
	//        void inc();
	//        T get() const;
	//        bool equals(const const_iterator_local& that) const;
	//    };
	//    const_iterator_local begin_local() const { };
	//    const_iterator_local end_local() const   { };
public:
	using value_type = T;
	
	class const_iterator : public ForwardListPolymorphic<T>::ConstIteratorPolymorphic  {
		friend class ForwardListImpl<L,T>;
		typename L::const_iterator_local cil;
		//For polymorphic iterator, never used otherwise
		void inc() override { cil.inc(); }
		T get() const override { return cil.get(); }
		bool equals(const typename ForwardListPolymorphic<T>::ConstIteratorPolymorphic& t) const override {
			try { //Maybe this can be sped up without the exception and with a reinterpret_cast
				const const_iterator& that = dynamic_cast<const const_iterator&>(t);
				return cil.equals(that.cil);
			} catch (const std::bad_cast& e) { return false; }
		}

                std::unique_ptr<typename ForwardListPolymorphic<T>::ConstIteratorPolymorphic> clone() const override { return std::make_unique<const_iterator>(*this); }
	public:
		const_iterator(const typename L::const_iterator_local& l) : cil(l) { }
		const_iterator& operator++()    {  cil.inc(); return (*this); }
		const_iterator  operator++(int) {  const_iterator old(cil); cil.inc(); return old; }
		bool operator==(const const_iterator& that) const { return cil.equals(that.cil); }
		bool operator!=(const const_iterator& that) const { return !cil.equals(that.cil); }
		T operator*() const { return cil.get(); }
	};

	const_iterator begin() const { return const_iterator(static_cast<const L*>(this)->begin_local()); }
	const_iterator end()   const { return const_iterator(static_cast<const L*>(this)->end_local());   }

	T front() const { return *(begin()); }
	
protected:
	std::unique_ptr<typename ForwardListPolymorphic<T>::ConstIteratorPolymorphic> make_iterator_begin() const override {
		return std::make_unique<const_iterator>(static_cast<const L*>(this)->begin_local());
	}

	std::unique_ptr<typename ForwardListPolymorphic<T>::ConstIteratorPolymorphic> make_iterator_end() const override {
		return std::make_unique<const_iterator>(static_cast<const L*>(this)->end_local());
	}

	std::unique_ptr<ForwardListPolymorphic<T>> clone() const override
	{	return std::make_unique<L>(static_cast<const L&>(*this));    }
};


template<typename L, typename T>
std::ostream& operator<<(std::ostream& os, const ForwardListImpl<L,T>& list) {
	os<<"[";
	bool first = true;
	for (auto e : list) {
		if (first) first = false;
		else os<<",";
		os<<e<<std::flush;
	}
	os<<"]";
	return os;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const ForwardList<T>& l) {
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


#endif
