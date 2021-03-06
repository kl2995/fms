// join.h - remove one level of enumeration
#pragma once
#include "enumerator.h"

namespace iter {

	// {e0, e1, ...} => {e0[0], e0[1], ..., e1[0], e1[1], ...
	template<class I,
		class T = typename std::iterator_traits<I>::value_type::value_type
	>
	class join_ : public enumerator_<I,T,std::input_iterator_tag> {
		typename std::iterator_traits<I>::value_type _i;
	public:
		using enumerator_<I,T,std::input_iterator_tag>::i;

		join_()
		{ }
		join_(I i)
			: enumerator_<I,T,std::input_iterator_tag>(i), _i(*i)
		{ }

		explicit operator bool() const
		{
			return i;
		}
		T operator*() const
		{
			return *_i;
		}
		join_& operator++()
		{
			if (i) {
				if (_i)
					++_i;
				if (!_i) {
					++i;
					_i = *i;
				}
			}

			return *this;
		}
		join_ operator++(int)
		{
			join_ f(*this);

			operator++();

			return f;
		}
	};
	template<class I,
		class T = typename std::iterator_traits<I>::value_type::value_type
	>
	inline auto join(I i)
	{
		return join_<I,T>(i);
	}
	// bind
	// return

} // iter

#ifdef _DEBUG
#include "include/ensure.h"
#include "constant.h"
#include "fmap.h"

inline void test_join()
{
	{
/*		int a[] = {0,1,2};
	
		struct s {
			const int* a;
			s(const int* a) : a(a) { }
			auto operator()(int i) const
			{
				return ce(a + i, 3 - i);
			}
		};
		auto dd = fmap(s(a), e(a));
		auto c = join(dd);
		ensure (*c == 0);
		++c;
		ensure (*c == 1);
		++c;
		ensure (*c == 2);
		++c;
		ensure (*c == 1);
		++c;
		ensure (*c == 2);
		++c;
		ensure (*c == 2);
	}
	{
		int a[] = {1,0,2,0,0,3};
		auto aa = fmap([&](int i) { return ce(c(i),i); }, a);
		auto _a = join(aa);
		ensure (*_a == 1);
		++_a;
		ensure (!*_a);
		++_a;
		ensure (*_a == 2);
		++_a;
		ensure (*_a == 2);
		++_a;
		ensure (!*_a);
		++_a;
		ensure (!*_a);
		++_a;
		ensure (*_a == 3);
		++_a;
		ensure (*_a == 3);
		++_a;
		ensure (*_a == 3);
*/	}

}

#endif // _DEBUG