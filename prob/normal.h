// normal.h - normal distribution
#pragma once
#include <cmath>
#include "iter/enumerator/null.h"
#include "iter/accumulate.h"
#include "iter/expr.h"
#include "iter/util.h"
//#include "math/exp.h"
#include "poly/hermite.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
// template<typename T> constexpr T M_SQRT2 = sqrt(T(2));
#ifndef M_SQRT2 
#define M_SQRT2 1.41421356237309504880
#endif
// template<typename T> constexpr T M_SQRT2PI = sqrt(2*M_PI<T>);
#ifndef M_SQRT2PI
#define M_SQRT2PI 2.50662827463100050242
#endif

#define pi  M_PI
#define sqrt2pi  M_SQRT2PI
#define sqrt2 M_SQRT2

namespace prob {

	class marsaglia {};
	class bell_impl {};
	class erfc_impl {};

	template<class X, class I>
	struct std_normal {
		static X cdf(const X&);
	};
	template<class X>
	struct std_normal<X,bell_impl> {
		// 0.5(1 + sgn(x) sqrt(1 - exp(-2 x^2/pi)
		static X cdf(const X& x)
		{
			return X(0.5)*(1 + (x > 0 ? 1 : -1)*sqrt(1 - exp(-2*x*x/pi)));
		}
	};
	template<class X>
	struct std_normal<X,marsaglia> {
		// 0.5 + exp(-x*x/2) sum x^{2n + 1}/(2n + 1)!!/sqrt2pi
		static X cdf(const X& x)
		{
			return X(0.5) + x*sum0(ne(prod(c(x*x)/E_(2*n + 1))))*exp(-x*x/2)/sqrt2pi;
		}
	};
	template<class X>
	struct std_normal<X,erfc_impl> {
		static X cdf(const X& x)
		{
			return erfc(-x/sqrt2)/2;
		}
	};

	template<class X = double, class I = erfc_impl>
	struct normal {

		static X cdf/*<marsaglia>*/(const X& x)
		{
			return std_normal::cdf<X,I>(x);
		}
		
		static X pdf(const X& x)
		{
			return exp(-x*x/2)/sqrt2pi;
		}
		static X inv(const X& x)
		{
			return 0;
		}
		// n-th derivative
		static X ddf(size_t n, const X& x)
		{
			if (n == 0)
				return cdf(x);
			if (n == 1)
				return pdf(x);

			// (-1)^{n-1}H_{n-1}(x) e^{-x^2/2}/sqrt2pi
			return (n%2?-1:1)*at(n-1, hermite(x))*exp(-x*x/2)/sqrt2pi;
		}
	};

} // prob

#ifdef _DEBUG
#include <cassert>

using namespace prob;

inline void test_normal()
{/*
	auto x = normal<>::cdf(0);
	assert (x == 0.5);
	x = normal<>::cdf(1);

	ensure (normal<>::cdf(0) == normal<>::ddf(0,0));
	ensure (normal<>::pdf(0) == normal<>::ddf(1,0));
	ensure (0 == normal<>::ddf(2,0));
	ensure (1/sqrt2pi == normal<>::ddf(3,0));
	ensure (-0 == normal<>::ddf(4,0));
	x = normal<>::ddf(5,0);
*/}

#endif // _DEBUG