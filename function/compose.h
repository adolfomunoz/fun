#ifndef _FUNCTIONAL_COMPOSE_H_
#define _FUNCTIONAL_COMPOSE_H_

#include <utility>

namespace fun {

template<typename F1, typename F2>
class Compose
{
	F1   f1;
	F2   f2;
public:
	Compose(F1&& _f1,      F2&& _f2      ) : f1(std::forward<F1>(_f1)), f2(std::forward<F2>(_f2)) { }
	Compose(const F1& _f1, F2&& _f2      ) : f1(_f1)                  , f2(std::forward<F2>(_f2)) { }
	Compose(F1&& _f1     , const F2& _f2 ) : f1(std::forward<F1>(_f1)), f2(_f2)                   { }
	Compose(const F1& _f1, const F2& _f2 ) : f1(_f1)                  , f2(_f2)                   { }

	template<typename... Args>
	auto operator()(Args&&... args) const 
	{	return f1(f2(std::forward<Args>(args)...));		}
};

/**************************************
 * fun::API                           *
 **************************************/

template<typename F1, typename F2>
auto compose(F1&& f1, F2&& f2)
{	return Compose<typename std::remove_reference<F1>::type,typename std::remove_reference<F2>::type>(std::forward<F1>(f1),std::forward<F2>(f2));	} 

template<typename F1, typename F2, typename... Fs>
auto compose(F1&& f1, F2&& f2, Fs&&... fs)
{	return compose(Compose<typename std::remove_reference<F1>::type,typename std::remove_reference<F2>::type>(std::forward<F1>(f1),std::forward<F2>(f2)), std::forward<Fs>(fs)...);	}

}; //namespace fun

#endif
