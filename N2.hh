#ifndef N2_HH
#define N2_HH

#include <iostream>

enum Error {
	DivideByZero,
	BadValue
};

class N2 {
protected:
	int _x;
	int _y;
public:
	N2();
	N2(int, int);
	int x() const;
	int y() const;
	N2 operator+(const N2&) const;
	N2 operator-(const N2&) const;
	N2 operator/(int) const;
friend std::ostream& operator<<(std::ostream&, const N2&);
};

#endif // N2_HH
