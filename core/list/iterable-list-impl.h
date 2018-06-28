#pragma once

#include <memory>
#include <iostream>
#include <sstream>

namespace fun
{

/**
 * Polymorphic version, base class of all forward lists
 **/
template<typename T>
class IterableListPolymorphic {

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
	virtual std::unique_ptr<IterableListPolymorphic<T>> clone() const = 0;
};

/**
 * Implementation version with CRPT, not polymorphic
 **/
template<typename L, typename T>
class IterableListImpl : public IterableListPolymorphic<T> {
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
	
	class const_iterator : public IterableListPolymorphic<T>::ConstIteratorPolymorphic  {
		friend class IterableListImpl<L,T>;
		typename L::const_iterator_local cil;
		//For polymorphic iterator, never used otherwise
		void inc() override { cil.inc(); }
		T get() const override { return cil.get(); }
		bool equals(const typename IterableListPolymorphic<T>::ConstIteratorPolymorphic& t) const override {
			//This should work in compile time and risky in runtime (but should not happen anything wrong)
			return this->cil.equals(static_cast<const const_iterator&>(t).cil);
//			try { //Maybe this can be sped up without the exception and with a reinterpret_cast
//				const const_iterator& that = dynamic_cast<const const_iterator&>(t);
//				return cil.equals(that.cil);
//			} catch (const std::bad_cast& e) { return false; }
		}

                std::unique_ptr<typename IterableListPolymorphic<T>::ConstIteratorPolymorphic> clone() const override { return std::make_unique<const_iterator>(*this); }
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
	std::unique_ptr<typename IterableListPolymorphic<T>::ConstIteratorPolymorphic> make_iterator_begin() const override {
		return std::make_unique<const_iterator>(static_cast<const L*>(this)->begin_local());
	}

	std::unique_ptr<typename IterableListPolymorphic<T>::ConstIteratorPolymorphic> make_iterator_end() const override {
		return std::make_unique<const_iterator>(static_cast<const L*>(this)->end_local());
	}

	std::unique_ptr<IterableListPolymorphic<T>> clone() const override
	{	return std::make_unique<L>(static_cast<const L&>(*this));    }
};


template<typename L, typename T>
std::ostream& operator<<(std::ostream& os, const IterableListImpl<L,T>& list) {
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






};

