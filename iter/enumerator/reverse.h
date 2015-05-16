// reverse.h
#pragma once
#include "../enumerator.h"

namespace iter {

	// reverse enumerator
	template<class T>
	class reverse_enumerator : public enumerator<T*,T> {
	public:
		using enumerator<T*,T>::i;

		reverse_enumerator()
		{ }
		reverse_enumerator(T* i)
			: enumerator<T*,T>(--i) // just like reverse iterators
		{ }

		operator bool() const
		{
			return true;
		}

		T operator*() const
		{
			return *i;
		}
		reverse_enumerator& operator++()
		{
			--i;

			return *this;
		}
		reverse_enumerator operator++(int)
		{
			reverse_enumerator i_(*this);

			--i;

			return i_;
		}
	};
	template<class T>
	inline reverse_enumerator<T> make_renumerator(T* i)
	{
		return reverse_enumerator<T>(i);
	}
	template<class T>
	inline reverse_enumerator<T> re(T* i)
	{
		return reverse_enumerator<T>(i);
	}

} // iter


#ifdef _DEBUG
#include <cassert>

using namespace iter;

inline void test_enumerator_reverse()
{
}

#endif // _DEBUG