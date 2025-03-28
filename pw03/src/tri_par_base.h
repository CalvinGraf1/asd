//
//  tri_rapide.h
//
//  Created by Alan Sottile, Calvin Graf, Lucas Hussain on 24.03.2023.
//  HEIG-VD | ASD | Labo 3 | L3G2
//

#ifndef TRI_PAR_BASE
#define TRI_PAR_BASE

#include <iterator>
#include <array>
#include <type_traits>
#include "some_bits.h"
#include <vector>

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
<<<<<<< HEAD
    using T = typename Iterator::value_type;
=======
	using T = typename Iterator::value_type;
>>>>>>> 2591415e1623f7ac57a0a12eb8931d6747c3dadb

	const size_t BASE = 1 << NBITS;
	std::vector<T> tmp(std::distance(first, last)); // Vecteur temporaire de la
	// même taille que notre vecteur

	for (size_t pos = 0; pos < (std::numeric_limits<T>::digits)/NBITS; pos++) {
		SomeBits<T> index_fn(NBITS, pos);
		tri_comptage(first, last, tmp.begin(), index_fn, BASE);
		// Recopier le vecteur tmp dans notre liste
		std::swap_ranges(first, last, tmp.begin());
	}

}

#endif