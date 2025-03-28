#ifndef TRI_PAR_BASE
#define TRI_PAR_BASE

#include <iterator>
#include <array>
#include <type_traits>
#include "some_bits.h"

template<typename Iterator, typename Fn>
void tri_comptage(Iterator first, Iterator last, Iterator output_first, Fn index_fn, size_t N)
{
	size_t* C = new size_t[N]();

	for(auto it = first; it != last; ++it) {
		++C[index_fn(*it)];
	}

	size_t idx = 0;
	for(size_t i = 0; i < N; ++i) {
		size_t tmp = C[i];
		C[i] = idx;
		idx += tmp;
	}

	for (Iterator it = first; it != last; ++it) {
		*(output_first + C[index_fn(*it)]) = *it;
		++C[index_fn(*it)];
	}
}

template<typename Iterator, size_t NBITS>
void tri_par_base(Iterator first, Iterator last)
{
    using T = typename Iterator::value_type;
    static_assert(std::is_unsigned<T>::value);

    // a compléter

}



#endif