#pragma once

#include <exception>
#include <functional>
#include <tuple>

namespace fun {
	

class PatternMatchingException : public std::exception {
public:
	const char* what() const noexcept override { return "Non-exhaustive patterns."; }
};


/*
template<typename... Clauses>
class Pattern {
public:
	template<typename F, typename... Args>
	auto match_and_evaluate(const F& f, Args&&... args) const {
		return std::nullopt;
	}
};
*/

template<typename Clause, typename... Clauses>
class Pattern {
	Clause clause;
	Pattern<Clauses...> pattern_rest;
	
	template <typename F>
	auto eval(const F& f, std::tuple<>&& args) const {
		return f();
	}
	
	template <typename F, typename... Args>
	auto eval(const F& f, std::tuple<Args...>&& args) const {
		return std::invoke(f,std::forward<std::tuple<Args...>>(args));
	}
public:
	Pattern(Clause&& clause, Pattern<Clauses...>&& pattern_rest) :
		clause(std::forward<Clause>(clause)), pattern_rest(std::forward<Pattern<Clauses...>>(pattern_rest)) { }

	template<typename F, typename Arg, typename... Args2>
	auto match_and_evaluate(const F& f, Arg&& a, Args2&&... args) const -> 
			std::optional<decltype(pattern_rest.match_and_evaluate(eval(f, clause.params(std::forward<Arg>(a))),std::forward<Args2>(args)...))> {
		if (clause.match(std::forward<Arg>(a))) return pattern_rest.match_and_evaluate(eval(f, clause.params(std::forward<Arg>(a))),std::forward<Args2>(args)...);
		else return {};
	}	
};

template<typename Clause>
class Pattern<Clause> {
	Clause clause;

	template <typename F>
	auto eval(const F& f, std::tuple<>&& args) const {
		return f();
	}
	
	template <typename F, typename... Args>
	auto eval(const F& f, std::tuple<Args...>&& args) const {
		return std::invoke(f,std::forward<std::tuple<Args...>>(args));
	}
public:
	Pattern(Clause&& clause) : clause(std::forward<Clause>(clause)) { }

	template<typename F, typename Arg>
	auto match_and_evaluate(const F& f, Arg&& a) const -> std::optional<decltype(this->eval(f,clause.params(std::forward<Arg>(a))))>{
		if (clause.match(std::forward<Arg>(a))) return eval(f, clause.params(std::forward<Arg>(a)));
		else return {};
	}	
};

//Maybe later we need to add back the function so we check that the patterns make sense

/*
template<typename PF, typename... Patterns>
class PatternMatching { 
public:
	template<typename... Args>
	int operator()(Args&&... args) const { throw(PatternMatchingException()); }
};
*/

template<typename Pattern1, typename Function1, typename... Rest>
class PatternMatching { 
	Pattern1  p;
	Function1 f;
	PatternMatching<Rest...> rest;
public:
	PatternMatching(const Pattern1& p, const Function1& f, const Rest&... r) :
		p(p),f(f), rest(r...) {}

	template<typename... Args2>
	auto operator()(Args2&&... args) const { 
		return p.match_and_evaluate(f,std::forward<Args2>(args)...).value_or(rest(std::forward<Args2>(args)...));
	}
};

template<typename Pattern1, typename Function1>
class PatternMatching<Pattern1,Function1> { 
	Pattern1  p;
	Function1 f;
public:
	PatternMatching(const Pattern1& p, const Function1& f) :
		p(p),f(f) {}

	template<typename... Args2>
	auto operator()(Args2&&... args) const { 
		auto the_optional = p.match_and_evaluate(f,std::forward<Args2>(args)...);
		if (the_optional.has_value()) return the_optional.value();
		else throw PatternMatchingException();
	}
};

template<typename Pattern1, typename Function1, typename... Rest>
PatternMatching<Pattern1,Function1,Rest...> function_pattern_matching(Pattern1&& p1, Function1&& f1, Rest&&... rest) {
	return PatternMatching<std::decay_t<Pattern1>,std::decay_t<Function1>,std::decay_t<Rest>...>(std::forward<Pattern1>(p1), std::forward<Function1>(f1), std::forward<Rest>(rest)...);
}


class ClauseWildcard {
public:
	template<typename Arg>
	constexpr bool match(const Arg& arg)  const { return true;    }
	
	template<typename Arg>
	constexpr auto params(const Arg& arg) const { return std::tuple<>(); }
};

template<typename Value>
class ClauseConstant {
	Value v;
	
public:
	ClauseConstant(Value&& v) : v(std::forward<Value>(v)) {}
	ClauseConstant(const Value& v) : v(v) {}

	template<typename Arg>
	constexpr bool match(const Arg& arg)  const { return arg==v;    }
	
	template<typename Arg>
	constexpr auto params(const Arg& arg) const { return std::tuple<>(); }
};

class ClauseAsIs {
public:
	template<typename Arg>
	constexpr bool match(const Arg& arg)  const { return true;    }
	
	template<typename Arg>
	constexpr auto params(Arg&& arg) const { return std::make_tuple(std::forward<Arg>(arg)); }
};

ClauseAsIs _x; //So the symbol _x means "get this stuff" as oposed to "ignore this stuff".

template<typename C>
struct IsClause {
	template<typename U>
	static auto test(U*) -> typename std::is_same<decltype(std::declval<U>().match(nullptr)), bool>;
	template<typename>
	static constexpr std::false_type test(...);

	static constexpr bool value = decltype(test<C>(nullptr))::value; 
};


auto clause(Section&& s) {
	return ClauseWildcard();
}

template<typename Clause>
auto clause(Clause&& c, typename std::enable_if_t<IsClause<Clause>::value>* enabler = nullptr) {
	return std::forward<Clause>(c);
}

template<typename Clause>
auto clause(Clause&& c, typename std::enable_if_t<!IsClause<Clause>::value>* enabler = nullptr) {
	return ClauseConstant<std::decay_t<Clause>>(std::forward<Clause>(c));
}

template<typename Clause, typename... Clauses>
auto pattern(Clause&& c, Clauses&&... clauses) {
	return Pattern(clause(c), pattern(clauses...));
}

template<typename Clause>
auto pattern(Clause&& c) {
	return Pattern<decltype(clause(c))>(clause(c));
}


	
	
	
}