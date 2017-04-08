#ifndef _FUNCTIONAL_SMART_AUTO_H_
#define _FUNCTIONAL_SMART_AUTO_H_

#include <memory>
#include "../list/core/forward-list.h"

namespace fun
{

template<typename T>
ForwardList<T> smart_auto_test(const ForwardListPolymorphic<T>&);


#ifdef EIGEN_CORE_H
//This works with Eigen, which is awesome
template<typename Derived>
Eigen::Matrix<typename Derived::Scalar, Derived::RowsAtCompileTime, Derived::ColsAtCompileTime> smart_auto_test(const Eigen::MatrixBase<Derived>&);
template<typename Derived>
Eigen::Array<typename Derived::Scalar,  Derived::RowsAtCompileTime, Derived::ColsAtCompileTime> smart_auto_test(const Eigen::ArrayBase<Derived>&);
#endif

void smart_auto_test(...);

//Smart auto cast for non-checked types return void, so we specialize smart_auto for void 
template<typename T, typename _type = decltype(smart_auto_test(std::declval<T>()))>
struct smart_auto {
	using type = _type;
};

template<typename T>
struct smart_auto<T,void> {
	using type = T;
};
};


#endif
