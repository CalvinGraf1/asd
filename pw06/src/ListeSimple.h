#ifndef LISTE_H
#define LISTE_H

#include "LSIterator.h"
#include <utility> // std::swap;

template<typename T>
class ListeSimple {
public:
    using value_type = T;
    using reference = T &;
    using const_reference = T const &;

private:
    struct Maillon {
        value_type valeur;
        Maillon *suivant;
    };

    Maillon avant_premier;

public:
    using iterator = LSIterator<value_type>;
    friend iterator;

    using const_iterator = LSConstIterator<value_type>;
    friend const_iterator;

    const_iterator cbegin() const noexcept {
        return const_iterator(avant_premier.suivant);
    }

    iterator begin() noexcept { return iterator(avant_premier.suivant); }

    const_iterator begin() const noexcept { return cbegin(); }

    ListeSimple() : avant_premier{value_type{}, nullptr} {
    }

    // end, cend, before_begin, cbefore_begin, empty, front
    const_iterator cend() const noexcept { return const_iterator(nullptr); }

    iterator end() noexcept { return iterator(nullptr); }

    const_iterator end() const noexcept { return cend(); }

    const_iterator cbefore_begin() const noexcept {
        return const_iterator(cbegin() - 1);
    }

    iterator before_begin() noexcept { return iterator(begin() - 1); }

    const_iterator before_begin() const noexcept { return cbefore_begin(); }

    bool empty() const noexcept { return begin() == nullptr; }

    reference front() noexcept { return *begin(); }

    const_reference front() const noexcept { return *begin(); }

    // insert_after, erase_after, splice_after, push_front, pop_front,
    void insert_after(Maillon m, size_t valeur) {
        assert(m != NULL);
        m.suivant = new Maillon(valeur, m.suivant);
    }

    void erase_after(Maillon m) noexcept {
        assert(m != NULL);
        assert(m.suivant != NULL);
        Maillon tmp = m.suivant;
        m.suivant = tmp.suivant;
        ::operator delete(tmp);
    }

    void splice_after(Maillon m, Maillon debut, Maillon fin) const {
        if (debut == fin)
            return;

		  Maillon tempFinSuivant = fin.suivant;
		  fin.suivant = m.suivant;
		  m.suivant = debut.suivant;
		  debut.suivant = tempFinSuivant;
    }

    void push_front(size_t valeur) {
        insert_after(before_begin(), valeur);
    }

    void pop_front() noexcept {
        erase_after(before_begin());
    }

    // swap, sort, ainsi que constructeur, opérateur d'affectation et destructeur

	 ListeSimple & operator=(const ListeSimple & lst) {
		 if(this == lst) return this;
		 if(empty()) while(begin() != NULL) pop_front();

		 Maillon* temp = lst.front();
		 while (temp != nullptr) {
			 push_front(temp->valeur);
			 temp = temp->next;
		 }
	 }

    void swap(Maillon m1, Maillon m2) {
        std::swap(&m1,&m2); // à voir si juste
    }

    void sort() {
        if (!empty()) {
            Maillon j = avant_premier.suivant;
            while (j != end()) {
                Maillon iMin = j;
                Maillon i = j.suivant;
                while (i != end()) {
                    if (i.valeur < iMin.valeur) {
                        iMin = i;
                    }
                    i = i.suivant;
                }
                splice_after(iMin, j,j); // peut etre utiliser swap
                j = iMin.suivant;
            }
        }
    }
};

#endif //LISTE_H
