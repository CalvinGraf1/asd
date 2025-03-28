#ifndef ASD_LABS_UTIL_H
#define ASD_LABS_UTIL_H

#include <ostream> // std::ostream

class C {
   int valeur;
	static int count;

	friend std::ostream& operator<<(std::ostream& out, C const& c);
	friend std::istream& operator>>(std::istream& in, C& c);
	friend bool operator==(const C& lhs, const C& rhs);
	friend bool operator!=(const C& lhs, const C& rhs);
	friend bool operator<(const C& lhs, const C& rhs);
	friend bool operator>(const C& lhs, const C& rhs);
	friend bool operator<=(const C& lhs, const C& rhs);
	friend bool operator>=(const C& lhs, const C& rhs);

	friend int getCount();
	friend void resetCount();
public:
	C();
   C(int i);
   C(const C& c);
	~C();
   C& operator= (const C& other);
};

int getCount();

void resetCount();

#endif //ASD_LABS_UTIL_H
