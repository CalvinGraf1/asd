#ifndef TRI_RAPIDE
#define TRI_RAPIDE


template<typename Iterator>
Iterator partition(Iterator first, Iterator last) {
	Iterator i = first - 1;
	Iterator j = last;
	Iterator pivot = first + (last - first) / 2;

	while (true) {
		do {
			++i;
		} while (*i < *pivot);

		do {
			--j;
		} while (*pivot < *j && j != first);

		if (i >= j)
			break;

		iter_swap(i, j);
	}
	iter_swap(i, pivot);
	return i;
}

template<typename Iterator>
void tri_rapide(Iterator first, Iterator last) {
	if (distance(first, last) <= 1)
		return; // Cas trivial (vecteur de 1 ou 0)

	Iterator pivot = partition(first, last);

	tri_rapide(first, pivot);
	tri_rapide(pivot + 1, last);
}

#endif