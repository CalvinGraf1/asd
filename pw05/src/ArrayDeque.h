#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <cstddef> // std::size_t
#include <ostream> // std::ostream
// Ajoutez si nécessaire d'autres inclusions de librairies
#include <cassert>
#include <memory>

template<class T>
class ArrayDeque {
public:
	using value_type = T;
	using reference = T &;
	using const_reference = const T &;
	using pointer = T *;
	using size_type = std::size_t;

	ArrayDeque(size_type _capacite = 0) : debut(0),
													  taille(0),
													  capacite(_capacite),
													  buffer(nullptr) {
		if (capacite)
			buffer = reinterpret_cast<pointer> (
				::operator new(capacite * sizeof(value_type)));
	}

	// Placez ici les méthodes publiques nécessaires pour passer le codecheck
	ArrayDeque(const ArrayDeque<value_type> &other)
		: debut(other.debut), taille(other.taille), capacite(other.capacite), buffer
		(nullptr) {

		if(other.capacite) {
			ArrayDeque<value_type> tmp(other.capacite);
			for (size_type i = 0; i < other.taille; ++i) {
				tmp.push_back(other[i]);
			}
			swap(tmp);
		}
	}

	~ArrayDeque() {
		if (buffer) // S'il y a des données à enlever ...
			while (taille)
				pop_front();

		::operator delete(buffer);
	}

	ArrayDeque<value_type> &operator=(const ArrayDeque<value_type>& other) {
		if (this != &other) {
			ArrayDeque tmp(other);
			swap(tmp);
		}
		return *this;
	}

	void shrink_to_fit() {
		resize(taille);
	}

	void push_back(const_reference v) {
		if (taille >= capacite)
			resize(nouvelle_capacite());

		assert(taille < capacite);
		size_type apres = i_physique(taille);
		new(buffer + apres) value_type(v);
		++taille;
	}

	void push_front(const_reference v) {
		if (taille >= capacite)
			resize(nouvelle_capacite());

		size_type avant = i_physique(capacite - 1);
		new(buffer + avant) value_type(v);
		debut = avant;
		++taille;
	}

	void pop_back() {
		assert(taille != 0);
		size_type apres = i_physique(taille - 1);
		std::destroy_at(buffer + apres);
		--taille;
	}

	void pop_front() {
		assert(taille != 0);
		std::destroy_at(buffer + debut);
		debut = i_physique(1);
		--taille;
	}


	const_reference front() const { // rvalue
		return buffer[debut];
	}

	reference front() { // lvalue
		return buffer[debut];
	}

	const_reference back() const { // rvalue
		return buffer[i_physique(taille - 1)];
	}

	reference back() { // lvalue
		return buffer[i_physique(taille - 1)];
	}

	void swap(ArrayDeque<value_type>& other) {
		std::swap(buffer, other.buffer);
		std::swap(capacite, other.capacite);
		std::swap(debut, other.debut);
		std::swap(taille, other.taille);
	}

	bool empty() const noexcept {
		return taille == 0;
	};

	size_type size() const noexcept {
		if (taille and capacite)
			return taille;
	};

	size_type capacity() const noexcept {
		return capacite;
	}

	const_reference operator[](size_type i) const { // rvalue
		return buffer[i_physique(i)];
	}

	reference operator[](size_type i) { // lvalue
		return buffer[i_physique(i)];
	}

private:
	pointer buffer;
	size_type capacite;
	size_type debut;
	size_type taille;

	// Placez ici les méthodes privées qui permettent de rendre votre code plus clair
	size_type i_physique(const size_type& i_logique) const {
		return (debut + i_logique) % capacite;
	}

	size_type nouvelle_capacite() {
		if (capacite)
			return 2 * capacite;
		return 1;
	}

	void resize(const size_type& size) {
		ArrayDeque<value_type> tmp(size);
		for (size_type i = 0; i < taille; i++) {
			tmp.push_back(buffer[i_physique(i)]);
		}
		swap(tmp);
	}

};

template<typename T>
inline
std::ostream &operator<<(std::ostream &s, const ArrayDeque<T> &v) {
	s << "(" << v.size() << "/" << v.capacity() << ") : ";
	if (not v.empty())
		s << v.front() << " -> " << v.back() << " : ";
	s << "[";
	for (int i = 0; i < v.size(); ++i) {
		s << v[i];
		if (i != v.size() - 1)
			s << ", ";
	}
	s << "]";
	return s;
}


#endif /* ArrayDeque_hpp */
