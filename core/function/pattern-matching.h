#pragma once

#include <exception>
#include <functional>
#include <tuple>

namespace fun {
	
template<typename Classes, typename Arg, typename... Args> 
struct PatternFunction { 
	using return_type = typename PatternFunction<Classes,Args...>::return_type;
};

template<typename Classes, typename Ret> 
struct PatternFunction { 
	using return_type = Arg;
};

class PatternMatchingException : public std::exception {
public:
	const char* what() const override { return "None of the patterns matched the input."; }
};

template<typename PF, typename... Patterns>
class PatternMatching { 
public:
	template<typename... Args>
	int operator()(Args&&... args) const { throw(PatternMatchingException()); }
};

template<typename Classes, typename... Args, typename Pattern1, typename Function1, typename... Rest>
class PatternMatching<PatternFunction<Classes,Args...>,Pattern1,Function1,Rest...> { 
	Pattern1  p;
	Function1 f;
	PatternMatching<PatternFunction<Classes,Args...>,Rest...> rest;
public:
	template<typename... Args>
	auto operator()(Args&& args) const { 
		return p.match_and_evaluate(f,std::forward<Args>(args)...).value_or(rest(std::forward<Args>(args)...));
	}
};

template<typename... Clauses>
class Pattern {
public:
	template<typename F, typename... Args>
	auto match_and_evaluate(F&& f, Args&&... args) const {
		return nullopt;
	}
};

template<typename Clause, typename... Clauses>
class Pattern<Clause, Clauses...> {
	Clause clause;
	Pattern<Clauses...> pattern_rest;
	
	template <typename F, typename A2, typename... Args2>
	auto eval(F&& f, A2&& a, Args2&&... args) const {
		return pattern_rest.match_and_evaluate(
			std::invoke(f,clause.params(std::forward<A2>(a))),std::forward<Args2>(args)...);
	}
public:
	Pattern(Clause&& clause, Pattern<Clauses...>&& pattern_rest) :
		clause(std::forward<Clause>(clause)), pattern_rest(std::forward<Pattern<Clauses...>>(pattern_rest)) { }

	template<typename F, typename A2, typename... Args2>
	std::optional<decltype(eval(std::declval<F>(),std::declval<A2>(),std::declval<Args>()...))>  match_and_evaluate(F&& f, A2&& a, Args2&&... args) const {
		if (clause.match(std::forward<A2>(a))) return eval(std::forward<F>(f), std::forward<A2>(a),std::forward<Args2>(args)...);
		else return {};
	}	
};

class ClauseWildcard {
public:
	template<typename Arg>
	constexpr bool match(const Arg& arg)  const { return true;    }
	
	template<typename Arg>
	constexpr auto params(const Arg& arg) const { std::tuple<>(); }
};

template<typename Value>
class ClauseConstant {
	Value v;
	
public:
	ClauseConstant(Value&& v) : v(std::forward<Value>(v)) {}
	ClauseConstant(const Value& v) : v(v);

	template<typename Arg>
	constexpr bool match(const Arg& arg)  const { return arg==v;    }
	
	template<typename Arg>
	constexpr auto params(const Args& arg) const { std::tuple<>(); }
};

class ClauseWildcard {
public:
	template<typename Arg>
	constexpr bool match(const Arg& arg)  const { return true;    }
	
	template<typename Arg>
	constexpr auto params(const Arg& arg) const { std::tuple<>(); }
};


class ClauseAsIs {
public:
	template<typename Arg>
	constexpr bool match(const Arg& arg)  const { return true;    }
	
	template<typename Arg>
	constexpr auto params(Arg&& arg) const { std::make_tuple(std::forward<Arg>(arg)); }
};

ClauseAsIs _x; //So the symbol _x means "get this stuff" as oposed to "ignore this stuff".

template<typename C>
struct IsClause {
	template<typename U>
	static auto test(U*) -> typename std::is_same<decltype(std::declval<U>().match(nullptr)), bool>::type;
	template<typename>
	static constexpr std::false_type test(...);

	static constexpr bool value = decltype(test<T>(nullptr))::value; 
};

template<typename Clause, bool is_clause == typename IsClause<Clause>::value>
struct AsClause {		using type = std::decay_t<Clause>;		};
template<typename Value>
struct AsClause<Value,false> {		using type = ClauseConstant;		};

template<typename Clause, typename Clauses...>
auto pattern(Clause&& clause, Clauses&&... clauses) {
	return Pattern<typename AsClause<Clause>::type, Clauses...>(
		(typename AsClause<Clause>::type)(std::forward<Clause>(clause)),
		std::forward<Clauses>(clauses)...);
}

template<typename Clauses...>
auto pattern(const Section& s, Clauses&&... clauses) {
	return pattern(ClauseWildcard(),std::forward<Clauses>(clauses)...);
}


	
	
	
}