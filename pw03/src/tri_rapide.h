//
//  tri_rapide.h
//
//  Created by Alan Sottile, Calvin Graf, Lucas Hussain on 24.03.2023.
//  HEIG-VD | ASD | Labo 3 | L3G2
//

#ifndef TRI_RAPIDE
#define TRI_RAPIDE

template<typename Iterator>
Iterator partition(Iterator first, Iterator last) {
	Iterator i = first - 1;
	Iterator j = last;

<<<<<<< HEAD
	// Pivot = Valeur aléatoire entre first et last
	Iterator pivot = first + rand() % distance(first, last);

	while (true) {
=======
	while (first < last) {
>>>>>>> 2591415e1623f7ac57a0a12eb8931d6747c3dadb
		do {
			++i;
		} while (*i < *last);

		do {
			--j;
		} while (j > first and *last < *j);

<<<<<<< HEAD
		if (i >= j) // i et j se sont croisés
			break;
=======
		if (i >= j) break;
>>>>>>> 2591415e1623f7ac57a0a12eb8931d6747c3dadb

		std::swap(*i, *j);
	}
	std::swap(*i, *last);

	return i;
}

template<typename Iterator>
void tri_rapide(Iterator first, Iterator last) {
	while (first < last) {
		Iterator pivot = first + rand() % distance(first, last);
		std::swap(*pivot, *last);
		Iterator i = partition(first, last);

		if (i - first < last - i) {
			tri_rapide(first, i - 1);
			first = i + 1;
		} else {
			tri_rapide(i + 1, last);
			last = i - 1;
		}
	}
}

#endif