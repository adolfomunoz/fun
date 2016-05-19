#ifndef _FUNCTIONAL_RANDOM_H_
#define _FUNCTIONAL_RANDOM_H_

#include "../iterator/const_iterator.h"
#include "../function/function.h"
#include <type_traits>
#include <random>
#include <tuple>

namespace fun {

template<typename VT, typename RandomEngine = std::mt19937, bool is_integral = std::is_integral<VT>::value>
class RandomSequence
{
public:
	using seed_type = typename RandomEngine::result_type;
private:	
	std::tuple<VT,VT> range;
	seed_type seed;
	friend class const_iterator;
public:
	RandomSequence(const std::tuple<VT,VT>& _range = std::make_tuple(VT(),VT()), seed_type _seed = (std::random_device())()) : 
		range(_range), seed(_seed) { }

	using value_type = VT;

	class const_iterator : public ConstIteratorFacade<const_iterator>
	{
		friend class RandomSequence<VT>;
		RandomEngine random;
		std::uniform_real_distribution<VT> sample;	
	        typename RandomSequence<VT>::value_type value;

		const_iterator(const std::tuple<VT,VT>& range, seed_type seed) : 
			random(seed), sample(std::get<0>(range),std::get<1>(range)), value(sample(random)) { }

		const_iterator() { }
	public:
		void inc() { value = sample(random); }
		bool equals(const const_iterator& that) const { return false; }
		const typename RandomSequence<VT>::value_type operator*() const { return value; } 		
	};

	const_iterator begin() const { return const_iterator(range, seed);  }
	const_iterator end()   const { return const_iterator(); }
};

template<typename VT, typename RandomEngine>
class RandomSequence<VT, RandomEngine, true>
{
public:
	using seed_type = typename RandomEngine::result_type;
private:	
	std::tuple<VT,VT> range;
	seed_type seed;
	friend class const_iterator;
public:
	RandomSequence(const std::tuple<VT,VT>& _range = std::make_tuple(VT(),VT()), seed_type _seed = (std::random_device())()) : 
		range(_range), seed(_seed) { }

	using value_type = VT;

	class const_iterator : public ConstIteratorFacade<const_iterator>
	{
		friend class RandomSequence<VT>;
		RandomEngine random;
		std::uniform_int_distribution<VT> sample;	
	        typename RandomSequence<VT>::value_type value;

		const_iterator(const std::tuple<VT,VT>& range, seed_type seed) : 
			random(seed), sample(std::get<0>(range),std::get<1>(range)), value(sample(random)) { }

		const_iterator() { }
	public:
		void inc() { value = sample(random); }
		bool equals(const const_iterator& that) const { return false; }
		const typename RandomSequence<VT>::value_type operator*() const { return value; } 		
	};

	const_iterator begin() const { return const_iterator(range, seed);  }
	const_iterator end()   const { return const_iterator(); }
};

using random_seed_type = std::mt19937::result_type; 

template<typename VT>
auto random_sequence_(const std::tuple<VT,VT>& range, std::mt19937::result_type seed = (std::random_device())())
{	return RandomSequence<VT, std::mt19937>(range, seed);  }

/**************************************
 * fun::API                           *
 **************************************/
auto randomRs    = function<2>([] (std::mt19937::result_type seed, const auto& range) { return random_sequence_(range, seed); });
auto randoms     = function<1>([] (std::mt19937::result_type seed) { return random_sequence_(std::make_tuple(0.0f, 1.0f), seed); });
auto randomSeeds = function<1>([] (std::mt19937::result_type seed) { return random_sequence_(std::make_tuple((std::mt19937::result_type)(0), std::numeric_limits<std::mt19937::result_type>().max()), seed); });
auto toSeed      = [] (float f)            { float f1 = 1.0f - f; return *(reinterpret_cast<std::mt19937::result_type*>(&f1)); };

auto randomRsIO    = function<1>([] (const auto& range) { return random_sequence_(range); });
auto randomsIO     = [] () { return random_sequence_(std::make_tuple(0.0f, 1.0f)); };
auto randomSeedsIO = [] () { return random_sequence_(std::make_tuple((std::mt19937::result_type)(0), std::numeric_limits<std::mt19937::result_type>().max())); };



}; //namespace fun

#endif
