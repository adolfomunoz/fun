#ifndef _FUNCTIONAL_RANDOM_H_
#define _FUNCTIONAL_RANDOM_H_

#include "core/forward-list.h"
#include "../function/function.h"
#include <type_traits>
#include <random>
#include <tuple>

namespace fun {

template<typename VT, typename RandomEngine = std::mt19937, bool is_integral = std::is_integral<VT>::value>
class RandomSequence : public ForwardListImpl<RandomSequence<VT, RandomEngine, is_integral>,VT>

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

	class const_iterator_local 
	{
		RandomEngine random;
		std::uniform_real_distribution<VT> sample;	
	        VT value;
	public:
		void inc() { value = sample(random); }
		VT get() const { return value; }
		bool equals(const const_iterator_local& that) const noexcept { return false; }
		const_iterator_local(const std::tuple<VT,VT>& range, seed_type seed) : 
			random(seed), sample(std::get<0>(range),std::get<1>(range)), value(sample(random)) { }
		const_iterator_local() { }
	};

	const_iterator_local begin_local() const { return const_iterator_local(range, seed);  }
	const_iterator_local end_local()   const { return const_iterator_local(); }
};

template<typename VT, typename RandomEngine>
class RandomSequence<VT, RandomEngine, true> : public ForwardListImpl<RandomSequence<VT, RandomEngine, true>,VT>
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

	class const_iterator_local
	{
		RandomEngine random;
		std::uniform_int_distribution<VT> sample;	
	        VT value;

	public:
		void inc() { value = sample(random); }
		VT get() const { return value; } 		
		bool equals(const const_iterator_local& that) const { return false; }
		const_iterator_local(const std::tuple<VT,VT>& range, seed_type seed) : 
			random(seed), sample(std::get<0>(range),std::get<1>(range)), value(sample(random)) { }
		const_iterator_local() { }
	};

	const_iterator_local begin_local() const { return const_iterator_local(range, seed);  }
	const_iterator_local end_local()   const { return const_iterator_local(); }
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
