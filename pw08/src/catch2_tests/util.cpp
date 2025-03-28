#include "util.h"

using std::exception;

int C::count = 0;

C::C() : valeur(0) {
	++count;
}

C::C(int i) : valeur(i) {
	++count;
}

C::C(const C &c) : valeur(c.valeur) {
	++count;
}

C::~C() {
	--count;
}

C &C::operator=(const C &other) {
	valeur = other.valeur;
	++count;
	return *this;
}


int getCount() {
	return C::count;
}

void resetCount() {
	C::count = 0;
}

std::ostream &operator<<(std::ostream &out, const C &c) {
	out << c.valeur;
	return out;
}

std::istream &operator>>(std::istream &in, C &c) {
	std::string input;
	in >> input;
	c.valeur = std::stoi(input);
	return in;
}

bool operator==(const C &lhs, const C &rhs) {
	return lhs.valeur == rhs.valeur;
}

bool operator!=(const C &lhs, const C &rhs) {
	return !(lhs == rhs);
}

bool operator<(const C &lhs, const C &rhs) {
	return lhs.valeur < rhs.valeur;
}

bool operator>(const C &lhs, const C &rhs) {
	return lhs.valeur > rhs.valeur;
}

bool operator<=(const C &lhs, const C &rhs) {
	return !(lhs > rhs);
}

bool operator>=(const C &lhs, const C &rhs) {
	return !(lhs < rhs);
}
